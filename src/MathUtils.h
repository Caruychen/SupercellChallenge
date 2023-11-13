#pragma once

#include <math.h>
#include <SFML/System.hpp>

float VecLength(sf::Vector2f a)
{
    return sqrtf(a.x*a.x + a.y*a.y);
}

void _clamp(float *value, const float max)
{
    if (abs(*value) > max)
        *value = *value < 0.f ? -max : max;
}

void _clamp(sf::Vector2f *value, const sf::Vector2f max)
{
    _clamp(&value->x, max.x);
    _clamp(&value->y, max.y);
}
