#pragma once

#include <SFML/Graphics.hpp>
#inlcude "Constants.h"

struct CollisionElement
{
    CollisionElement(
                     const float area,
                     const eTile tile,
                     const sf::FloatRect box
                     ) :
    m_area(area), m_tile(tile), m_box(box) {}
    
    float m_area;
    eTile m_tile;
    sf::FloatRect m_box;
};
