#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Constants.h"
#include "SharedContext.h"
#include "InputHandler.hpp"
#include "Window.h"

class Window;
class InputHandler;
class SharedContext;

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
    SharedContext   m_context;
    sf::Clock       m_clock;
    sf::Time        m_deltaTime;
    InputHandler    m_inputHandler;
    Window          m_window;
    sf::Font        m_font;
};
