#include "Entity.h"
#include "EntityHandler.h"
#include "SharedContext.h"
#include "MathUtils.h"
#include "Constants.h"
#include <cmath>

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
    sf::FloatRect viewRect = handler->getContext()->m_window->getViewRect();
    m_position += pos;
    
    if (m_position.x < 0)
        m_position.x = 0;
    else if (m_position.x + m_size.x > ScreenWidth)
        m_position.x = ScreenWidth - m_size.x;
    if (m_position.y < 0)
        m_position.y = 0;
    else if (m_position.y + m_size.y > ScreenHeight)
        m_position.y = ScreenHeight - m_size.y;
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
            if (m_isMoving)
                m_velocity.x *= 0.05f;
            else if (m_collidingY && abs(m_velocity.x) > abs(m_maxVelocity.x))
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

void Entity::_updateBox()
{
    m_box = sf::FloatRect(m_position.x, m_position.y, m_size.x, m_size.y);
}

void Entity::_checkCollisions()
{}

void Entity::_resolveCollisions()
{}

// Private
