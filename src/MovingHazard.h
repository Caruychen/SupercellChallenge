#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class MovingHazard: public Entity, public sf::Drawable
{
public:
    MovingHazard(
                 EntityHandler *handler,
                 const sf::Vector2f position,
                 const bool horizontal,
                 const float initialDirection);
    
    ~MovingHazard();
    
    void move(const float x, const float y);
    void move(sf::Vector2f pos);
    void update(void);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    bool _isInView(void) const;
    void _updateDirection(const float deltaSeconds);
    void _checkCollisions(void);
    void _resolveCollisions(void);

    sf::RectangleShape m_shape;
    sf::Color m_color;
    bool m_isHorizontal;
    float m_currentDirection;
    float m_timer;
};

