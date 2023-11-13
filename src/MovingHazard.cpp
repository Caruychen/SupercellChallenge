#include "MovingHazard.h"
#include "EntityHandler.h"
#include "SharedContext.h"
#include "Constants.h"
#include "Window.h"

MovingHazard::MovingHazard(
                           EntityHandler *handler,
                           const sf::Vector2f position,
                           const bool horizontal,
                           const float initialDirection):
Entity(handler,
       sf::Vector2f(HazardSize, HazardSize),
       sf::Vector2f(HazardMaxVelocity, HazardMaxVelocity),
       sf::Vector2f(HazardMaxAcceleration, HazardMaxAcceleration)),
m_shape(sf::RectangleShape(sf::Vector2f(HazardSize, HazardSize))),
m_color(sf::Color::Red),
m_isHorizontal(horizontal),
m_currentDirection(initialDirection),
m_timer(0.f)
{
    m_shape.setPosition(position);
    m_shape.setFillColor(m_color);
    setSpawnPosition(position);
    setPosition(position);
}

MovingHazard::~MovingHazard()
{}

void MovingHazard::move(const float x, const float y)
{
    move(sf::Vector2f(x, y));
}

void MovingHazard::move(sf::Vector2f pos)
{
    sf::FloatRect viewRect = m_handler->getContext()->m_window->getViewRect();
    m_position += pos;
    
    if (m_position.x < viewRect.left)
        m_position.x = viewRect.left;
    else if (m_position.x + m_size.x > viewRect.left + viewRect.width)
        m_position.x = (viewRect.left + viewRect.width) - m_size.x;
    if (m_position.y < viewRect.top)
        m_position.y = viewRect.top;
    else if (m_position.y + m_size.y > viewRect.top + viewRect.height)
        m_position.y = (viewRect.top + viewRect.height) - m_size.y;
    _updateBox();
}

void MovingHazard::update()
{
    if (!_isInView())
        return;
    const float deltaSeconds = m_handler->getContext()->m_deltaTime->asSeconds();
    _updateDirection(deltaSeconds);
    addVelocity(m_isHorizontal * m_currentDirection * m_acceleration.x * deltaSeconds,
                !m_isHorizontal * m_currentDirection * m_acceleration.y * deltaSeconds);
    move(m_velocity * deltaSeconds);
    _checkCollisions();
    _resolveCollisions();
    m_shape.setPosition(m_position);
}

void MovingHazard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!_isInView())
        return;
    target.draw(m_shape, states);
}

bool MovingHazard::_isInView() const
{
    sf::FloatRect viewRect = m_handler->getContext()->m_window->getViewRect();
    if (m_position.x < viewRect.left ||
        m_position.x + m_size.x > viewRect.left + viewRect.width ||
        m_position.y < viewRect.top ||
        m_position.y + m_size.y > viewRect.top + viewRect.height)
        return false;
    return true;
}

void MovingHazard::_updateDirection(const float deltaSeconds)
{
    m_timer += deltaSeconds;
    if (m_timer >= 2.f)
    {
        m_timer = 0.f;
        m_currentDirection *= -1;
    }
}

void MovingHazard::_checkCollisions()
{
    Player *player = m_handler->getPlayer();
    if (m_box.intersects(player->getBox()))
        player->respawn();
    Entity::_checkCollisions();
}

void MovingHazard::_resolveCollisions()
{
    if (m_collisions.empty())
        return;
    Map *map = m_handler->getContext()->m_map;
    for (CollisionElement &itr: m_collisions)
    {
        sf::FloatRect offset;
        if (itr.m_tile != eTile::eBlock &&
            itr.m_tile != eTile::eHazard &&
            itr.m_tile != eTile::eDoor)
            continue;
        if (!m_box.intersects(itr.m_box, offset))
            continue;
        float xDiff = m_box.left - itr.m_box.left;
        float yDiff = m_box.top - itr.m_box.top;
        if (offset.width <= offset.height)
            move((xDiff < 0 ? -offset.width: offset.width),0);
        else
            move(0, (yDiff < 0 ? -offset.height: offset.height));
    }
    m_collisions.clear();
}
