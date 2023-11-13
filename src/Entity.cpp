#include "Entity.h"

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
m_box(sf::FloatRect(m_position.x, m_position.y, size.x, size.y))
{}

Entity::~Entity()
{}

void Entity::move(const float x, const float y)
{
    move(sf::Vector2f(x, y));
}

void Entity::move(sf::Vector2f pos)
{}

void Entity::addVelocity(const float x, const float y)
{
    addVelocity(sf::Vector2f(x, y));
}

void Entity::addVelocity(const sf::Vector2f value)
{}

void Entity::accelerate(const float x, const float y)
{
    accelerate(sf::Vector2f(x, y));
}

void Entity::accelerate(const sf::Vector2f value)
{}

void Entity::addFriction(const float deltaSeconds)
{}

void Entity::update()
{}

void Entity::_updateBox()
{}

void Entity::_checkCollisions()
{}

void Entity::_resolveCollisions()
{}
