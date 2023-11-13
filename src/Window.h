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
    void shake();
    void shiftViewUp();
    
    void beginDraw();
    void endDraw();
    void draw(sf::Drawable &drawable);
    
    void setDone();
    bool isDone(void) const;
    sf::RenderWindow *getRenderWindow();
    sf::FloatRect getViewRect() const;
    
private:
    void _updateShake();
    
    SharedContext       *m_context;
    sf::RenderWindow    m_window;
    sf::FloatRect       m_viewRect;
    sf::View            m_view;
    bool                m_isDone;
    int                 m_shakeCount;
};
