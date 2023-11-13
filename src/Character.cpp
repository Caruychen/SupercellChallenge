#include "Character.h"
#include "EntityHandler.h"
#include "SharedContext.h"

Character::Character(
          EntityHandler *handler,
          const sf::Vector2f size,
          const sf::Vector2f maxVelocity,
          const sf::Vector2f maxAcceleration,
          const sf::Vector2f dashVelocity,
          const float accelerationRate,
          const float jumpVelocity
          ) :
Entity(handler, size, maxVelocity, maxAcceleration),
m_shape(sf::RectangleShape(size)),
m_color(sf::Color::Blue),
m_dashColor(sf::Color::Magenta),
m_dashVelocity(dashVelocity),
m_accelerationRate(accelerationRate),
m_jumpVelocity(jumpVelocity),
m_canJump(true),
m_canDash(true),
m_isWallJumping(false),
m_isDashing(false),
m_dashTimer(0.f),
m_currentDirection(1)
{
    m_shape.setPosition(0.f, 0.f);
    m_shape.setFillColor(m_color);
}

Character::~Character()
{}

void Character::move(const int direction)
{
    if (m_isDashing)
        return;
    const float deltaSeconds = m_handler->getContext()->m_deltaTime->asSeconds();
    if ((direction > 0 && m_velocity.x > -0.1f) ||
        (direction < 0 && m_velocity.x < 0.1f) ||
        m_isWallJumping)
        m_isMoving = true;
    accelerate(direction * m_accelerationRate * deltaSeconds, 0);
    m_currentDirection = direction;
    if (m_collidingX)
        m_velocity.y = std::min(0.f, m_velocity.y);
}

void Character::jump()
{
    if (m_isDashing || m_collidingYBottom || m_collidingX)
        m_canJump = true;
    if (!m_canJump)
        return;
    if (m_collidingX)
        m_isWallJumping = true;
    m_canJump = false;
    m_acceleration.y = std::min(0.f, m_acceleration.y);
    m_velocity.y = -m_jumpVelocity;
    if (m_collidingX)
        m_velocity.x = -m_currentDirection * m_jumpVelocity;
}

bool Character::dash()
{
    if (!m_canDash || m_isDashing)
        return false;
    m_canDash = false;
    m_isDashing = true;
    m_dashTimer = 0;
    m_acceleration = {0, 0};
    m_velocity = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_velocity.x = -m_dashVelocity.x;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_velocity.x = m_dashVelocity.x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_velocity.y = -m_dashVelocity.y;
        m_velocity.x *= 0.8f;
    }
    m_shape.setFillColor(m_dashColor);
    return true;
}

void Character::update(void)
{
    _persistDash();
    if (!m_isDashing)
        Entity::update();
    m_shape.setPosition(m_position);
    if (m_collidingYBottom || m_collidingX)
    {
        m_canDash = true;
        m_isWallJumping = false;
    }
    if (m_isDashing)
        m_isWallJumping = false;
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

void Character::_persistDash()
{
    const float deltaSeconds = m_handler->getContext()->m_deltaTime->asSeconds();
    
    if (m_isDashing)
        m_isMoving = true;
    if (m_dashTimer >= 0.15f)
    {
        if (m_isDashing)
            m_velocity.y *= 0.25;
        m_isDashing = false;
        m_shape.setFillColor(m_color);
    }
    if (!m_isDashing)
        return ;
    m_dashTimer += deltaSeconds;
    m_collidingY = false;
    m_collidingYBottom = false;
    Entity::move(m_velocity * deltaSeconds);
}
