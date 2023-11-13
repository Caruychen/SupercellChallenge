#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include "Constants.h"
#include "Window.hpp"

class Game
{
public:
    Game();
    ~Game();
    
    bool initialise();
    void update();
    void render();
    void restartClock();
    
    bool isRunning() const;

private:
    sf::Clock m_clock;
    sf::Time m_deltaTime;
    Window m_window;
    sf::Font m_font;
};
