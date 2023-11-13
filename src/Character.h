#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class EntityHandler;

class Character : public Entity, public sf::Drawable
{
public:
    Character(
              EntityHandler *handler,
              const sf::Vector2f size,
              const sf::Vector2f maxVelocity,
              const sf::Vector2f maxAcceleration,
              const sf::Vector2f dashVelocity,
              const float accelerationRate,
              const float jumpVelocity
              );
    ~Character();
    
    void move(const int direction);
    void jump();
    bool dash(int direction);
    
    virtual void update();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
private:
    void _persistDash();
    
    sf::RectangleShape  m_shape;
    sf::Color           m_color;
    sf::Color           m_dashColor;
    const sf::Vector2f  m_dashVelocity;
    const float         m_accelerationRate;
    const float         m_jumpVelocity;
    bool                m_canJump;
    bool                m_canDash;
    bool                m_isWallJumping;
    bool                m_isDashing;
    float               m_dashTimer;
    int                 m_currentDirection;
};
