#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Coin : public Entity, public sf::Drawable
{
public:
    Coin(
         EntityHandler *handler,
         const sf::Vector2f position);
    ~Coin();
    
    void update();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
private:
    void _checkCollisions();
    sf::CircleShape m_shape;
    sf::Color       m_color;
    bool            m_isCollected;
};
