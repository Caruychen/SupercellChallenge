#include "Player.h"
#include "EntityHandler.h"
#include "SharedContext.h"
#include "Window.h"
#include <iostream>

Player::Player(EntityHandler *handler) :
Character(handler,
         sf::Vector2f(PlayerWidth, PlayerHeight),
         sf::Vector2f(PlayerMaxVelocityX, PlayerMaxVelocityY),
         sf::Vector2f(PlayerMaxAccelerationX, PlayerMaxAccelerationY),
         sf::Vector2f(PlayerDashVelocityX, PlayerDashVelocityY),
         PlayerAcceleration,
         PlayerJumpVelocity),
m_score(0),
m_direction(0)
{
    m_text.setFont(*m_handler->getContext()->m_font);
    m_text.setCharacterSize(32);
    m_text.setFillColor(sf::Color::Yellow);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(2);
}

Player::~Player()
{}

void Player::setDirection(int direction)
{
    m_direction = direction;
}

void Player::handleMovementInput()
{
    m_isMoving = false;
    if (m_direction != 0)
        move(m_direction);
}

void Player::incrementScore()
{
    m_score++;
}

void Player::update()
{
    sf::FloatRect view = m_handler->getContext()->m_window->getViewRect();
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setString("Score " + std::to_string(m_score));
    m_text.setPosition(sf::Vector2f(
                                    view.left + view.width - textRect.width - 10,
                                    view.top));
    Character::update();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Character::draw(target, states);
    target.draw(m_text, states);
}
