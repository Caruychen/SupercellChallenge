#include "Entity.h"
#include "EntityHandler.h"
#include "SharedContext.h"
#include "Window.h"
#include "Map.h"
#include "MathUtils.h"
#include "Constants.h"
#include <cmath>
#include <iostream>

Entity::Entity(
               EntityHandler *handler,
               const sf::Vector2f size,
               const sf::Vector2f maxVelocity,
               const sf::Vector2f maxAcceleration) :
m_handler(handler),
m_size(size),
m_maxVelocity(maxVelocity),
m_maxAcceleration(maxAcceleration),
m_spawnPosition({0.f, 0.f}),
m_position({0.f, 0.f}),
m_velocity({0.f, 0.f}),
m_acceleration({0.f, 0.f}),
m_isMoving(false),
m_collidingX(false),
m_collidingY(false),
m_collidingYBottom(false),
m_box(sf::FloatRect(m_position.x, m_position.y, size.x, size.y)),
m_frictionTimer(0.f)
{}

Entity::~Entity()
{}

void Entity::move(const float x, const float y)
{
    move(sf::Vector2f(x, y));
}

void Entity::move(sf::Vector2f pos)
{
    sf::FloatRect viewRect = m_handler->getContext()->m_window->getViewRect();
    if ((abs(m_velocity.x) > abs(m_maxVelocity.x)) ||
        (abs(m_velocity.y) > abs(m_maxVelocity.y)))
        _dashLimiter(pos);
    m_position += pos;
    
    if (m_position.x < viewRect.left)
        m_position.x = viewRect.left;
    else if (m_position.x + m_size.x > viewRect.left + viewRect.width)
        m_position.x = (viewRect.left + viewRect.width) - m_size.x;
    if (m_position.y < viewRect.top)
        m_position.y = viewRect.top;
    else if (m_position.y + m_size.y > viewRect.top + viewRect.height)
        respawn();
    _updateBox();
}

void Entity::addVelocity(const float x, const float y)
{
    addVelocity(sf::Vector2f(x, y));
}

void Entity::addVelocity(const sf::Vector2f value)
{
    if (m_collidingY || abs(m_velocity.x) <= abs(m_maxVelocity.x))
    {
        m_velocity.x += value.x;
        _clamp(&m_velocity.x, m_maxVelocity.x);
    }
    m_velocity.y += value.y;
    _clamp(&m_velocity.y, m_maxVelocity.y);
}

void Entity::accelerate(const float x, const float y)
{
    accelerate(sf::Vector2f(x, y));
}

void Entity::accelerate(const sf::Vector2f value)
{
    if (!m_isMoving)
        m_acceleration.x = 0;
    m_acceleration += value;
    _clamp(&m_acceleration, m_maxAcceleration);
}

void Entity::applyFriction(const float deltaSeconds)
{
    m_frictionTimer += deltaSeconds;
    if (m_velocity.x != 0)
    {
        if (abs(m_velocity.x) < 1.f)
            m_velocity.x = 0.f;
        else if (m_frictionTimer > 0.01f)
        {
            if (!m_isMoving)
                m_velocity.x *= 0.05f;
            else if (!m_collidingY && abs(m_velocity.x) > abs(m_maxVelocity.x))
                m_velocity.x *= 0.95f;
        }
    }
    if (m_frictionTimer > 0.01f)
        m_frictionTimer = 0;
}

void Entity::update()
{
    const float deltaSeconds = m_handler->getContext()->m_deltaTime->asSeconds();
    accelerate(0, Gravity);
    addVelocity(m_acceleration.x * deltaSeconds, m_acceleration.y * deltaSeconds);
    applyFriction(deltaSeconds);
    move(m_velocity * deltaSeconds);
    m_collidingX = false;
    m_collidingY = false;
    m_collidingYBottom = false;
    _checkCollisions();
    _resolveCollisions();
}

void Entity::respawn()
{
    m_collisions.clear();
    m_position = m_spawnPosition;
    m_velocity = {0.f, 0.f};
    m_acceleration = {0.f, 0.f};
    m_isMoving = false;
    m_collidingX = false;
    m_collidingY = false;
    m_collidingYBottom = false;
    m_frictionTimer = 0.f;
    _updateBox();
}

void Entity::setSpawnPosition(const sf::Vector2f &pos)
{
    m_spawnPosition = pos;
}

void Entity::setPosition(const sf::Vector2f &pos)
{
    m_position = pos;
    _updateBox();
}
void Entity::setAcceleration(const float x, const float y)
{
    setAcceleration(sf::Vector2f(x, y));
}

void Entity::setAcceleration(const sf::Vector2f acc)
{
    m_acceleration = acc;
}

sf::Vector2f Entity::getPosition() const
{
    return m_position;
}

sf::FloatRect Entity::getBox() const
{
    return m_box;
}

void Entity::_updateBox()
{
    m_box = sf::FloatRect(m_position.x, m_position.y, m_size.x, m_size.y);
}

void Entity::_checkCollisions()
{
    Map *map = m_handler->getContext()->m_map;
    int fromX = floor(m_box.left / TileSize);
    int toX = floor((m_box.left + m_size.x) / TileSize);
    int fromY = floor(m_box.top / TileSize);
    int toY = floor((m_box.top + m_size.y) / TileSize);
    
    for (int row = fromY; row <= toY; ++row)
    {
        for (int col = fromX; col <= toX; ++col)
        {
            eTile tile = map->getTile(row, col);
            if (tile == eTile::eEmpty)
                continue;
            sf::FloatRect tileBounds = sf::FloatRect(
                                                     col * TileSize,
                                                     row * TileSize,
                                                     TileSize,
                                                     TileSize
                                                     );
            sf::FloatRect intersection;
            m_box.intersects(tileBounds, intersection);
            float area = intersection.width * intersection.height;
            m_collisions.push_back(CollisionElement(area, tile, tileBounds));
        }
    }
}

void Entity::_resolveCollisions()
{
    if (m_collisions.empty())
        return;
    std::sort(m_collisions.begin(), m_collisions.end(), _sortCollisions);
    Map *map = m_handler->getContext()->m_map;
    for (CollisionElement &itr: m_collisions)
    {
        sf::FloatRect offset;
        if (!m_box.intersects(itr.m_box, offset))
            continue;
        switch (itr.m_tile)
        {
            case eTile::eDoor:
                m_handler->progressPlayer();
            case eTile::eHazard:
                respawn();
                return;
            default:
                break;
        }
        float xDiff = m_box.left - itr.m_box.left;
        float yDiff = m_box.top - itr.m_box.top;
        if (offset.width <= offset.height)
        {
            move((xDiff < 0 ? -offset.width: offset.width) ,0);
            m_collidingX = true;
            m_velocity.x = 0;
            m_acceleration.x = 0;
        }
        else
        {
            move(0, (yDiff < 0 ? -offset.height: offset.height));
            m_collidingY = true;
            m_collidingYBottom = yDiff < 0;
            m_velocity.y = yDiff < 0 ? std::min(0.f, m_velocity.y) : 0;
            m_acceleration.y = yDiff < 0 ? std::min(0.f, m_acceleration.y) : 0;
        }
    }
    m_collisions.clear();
}

// Private

void Entity::_dashLimiter(sf::Vector2f &pos)
{
    const int increment = 40;
    sf::Vector2f tmp = m_position;
    sf::Vector2f incVector = {pos.x / increment, pos.y / increment};
    
    for (int i = 0; i < increment; ++i)
    {
        tmp += incVector;
        Map *map = m_handler->getContext()->m_map;
        sf::FloatRect box(tmp.x, tmp.y, m_size.x, m_size.y);
        int fromX = floor(tmp.x / TileSize);
        int toX = floor((tmp.x + m_size.x) / TileSize);
        int fromY = floor(tmp.y / TileSize);
        int toY = floor((tmp.y + m_size.y) / TileSize);
        
        for (int row = fromY; row <= toY; ++row)
        {
            for (int col = fromX; col <= toX; ++col)
            {
                if (map->getTile(row, col) == eTile::eEmpty)
                    continue;
                sf::FloatRect tileBounds = sf::FloatRect(
                                                         col * TileSize,
                                                         row * TileSize,
                                                         TileSize,
                                                         TileSize
                                                         );
                if (box.intersects(tileBounds))
                {
                    pos = {tmp.x - m_position.x, tmp.y - m_position.y};
                    return;
                }
            }
        }
    }
}

bool Entity::_sortCollisions(const CollisionElement &a, const CollisionElement &b)
{
    return (a.m_area > b.m_area);
}
