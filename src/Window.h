#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
struct SharedContext;

class Window
{
public:
    Window(SharedContext *context);
    ~Window();
    
    void create();
    void destroy();
    void update();
    
    void beginDraw();
    void endDraw();
    void draw(sf::Drawable &drawable);
    
    void setDone();
    bool isDone(void) const;
    sf::RenderWindow *getRenderWindow();
    
private:
    SharedContext *m_context;
    sf::RenderWindow m_window;
    bool m_isDone;
};
