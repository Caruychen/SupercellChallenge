//
//  Window.cpp
//  Platformer
//
//  Created by Caruy Chen on 13.11.2023.
//

#include "Constants.h"
#include "Window.hpp"

#include <SFML/Graphics.hpp>

Window::Window() : m_isDone(false)
{}

Window::~Window()
{}

void Window::create()
{
    m_window.create(sf::VideoMode(ScreenWidth, ScreenHeight), "Platformer");
    m_window.setFramerateLimit(60);
}

void Window::destroy()
{
    m_window.close();
}

void Window::update()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                setDone();
            default:
                break;
        }
    }
}

void Window::beginDraw()
{
    m_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
    m_window.display();
}

void Window::setDone()
{
    m_isDone = true;
}

bool Window::isDone() const
{
    return m_isDone;
}
