#pragma once

# include <SFML/Graphics.hpp>

struct MovingHazardData
{
    MovingHazardData(
                     const sf::Vector2f position,
                     const bool horizontal,
                     const float initialDirection):
    m_position(position),
    m_horizontal(horizontal),
    m_initialDirection(initialDirection) {}
    
    const sf::Vector2f m_position;
    const bool m_horizontal;
    const float m_initialDirection;
};
