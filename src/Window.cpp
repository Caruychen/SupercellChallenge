//
//  Window.cpp
//  Platformer
//
//  Created by Caruy Chen on 13.11.2023.
//

#include "Constants.h"
#include "Window.h"
#include "Map.h"
#include "SharedContext.h"

#include <SFML/Graphics.hpp>

Window::Window(SharedContext *context) :
m_context(context),
m_isDone(false),
m_shakeCount(0),
m_viewRect({0.f, 0.f, ScreenWidth, ScreenHeight}),
m_view(m_viewRect)
{
    m_context->m_window = this;
}

Window::~Window()
{
    destroy();
}

void Window::create()
{
    m_window.create(sf::VideoMode(ScreenWidth, ScreenHeight), "Platformer");
    m_window.setFramerateLimit(FramerateLimit);
    m_window.setKeyRepeatEnabled(false);
    m_view.setViewport({0.f, 0.f, 1.f, 1.f});
    sf::Vector2f mapSize = m_context->m_map->getSize();
    m_viewRect = {0, mapSize.y - ScreenHeight, ScreenWidth, ScreenHeight};
    m_view.reset(m_viewRect);
}

void Window::destroy()
{
    m_window.close();
}

void Window::update()
{
    m_view.reset(m_viewRect);
    _updateShake();
    m_window.setView(m_view);
}

void Window::shake()
{
    m_shakeCount = 4;
}

void Window::shiftViewUp()
{
    m_viewRect.top -= ScreenHeight;
}

void Window::beginDraw()
{
    m_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
    m_window.display();
}

void Window::draw(sf::Drawable &drawable)
{
    m_window.draw(drawable);
}

void Window::setDone()
{
    m_isDone = true;
}

bool Window::isDone() const
{
    return m_isDone;
}

sf::RenderWindow *Window::getRenderWindow()
{
    return &this->m_window;
}

sf::FloatRect Window::getViewRect() const
{
    return m_viewRect;
}

void Window::_updateShake()
{
    static float shakeTimer;
    const float deltaSeconds = m_context->m_deltaTime->asSeconds();
    shakeTimer += deltaSeconds;
    if (m_shakeCount > 0)
    {
        int direction = (m_shakeCount % 2 == 0) ? 1 : -1;
        m_view.reset(sf::FloatRect(
                                   m_viewRect.left + direction * m_shakeCount,
                                   m_viewRect.top + direction * m_shakeCount,
                                   ScreenWidth,
                                   ScreenHeight));
        if (shakeTimer > 0.05f)
        {
            shakeTimer = 0;
            --m_shakeCount;
        }
    }
}
