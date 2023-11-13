#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>

class Window
{
public:
    Window();
    ~Window();
    
    void create();
    void destroy();
    void update();
    void beginDraw();
    void endDraw();
    
    void setDone();
    bool isDone(void) const;
    
private:
    sf::RenderWindow m_window;
    bool m_isDone;
};
