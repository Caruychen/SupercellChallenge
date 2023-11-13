#pragma once

#include <SFML/Graphics.hpp>

class Window;
class InputHandler;

struct SharedContext
{
    SharedContext();
    Window  *m_window;
    InputHandler *m_inputHandler;
    sf::Time *m_deltaTime;
    sf::Clock *m_clock;
    sf::Font *m_font;
    
};
