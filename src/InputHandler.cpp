#include "InputHandler.h"
#include "SharedContext.h"
#include "EntityHandler.h"
#include "Window.h"
#include <iostream>

InputHandler::InputHandler(SharedContext *context) :
m_context(context),
m_direction(0),
m_pressingUp(false),
m_pressingLeft(false),
m_pressingRight(false)
{
    m_context->m_inputHandler = this;
}

InputHandler::~InputHandler()
{}

void InputHandler::pollEvents()
{
    sf::Event event;
    Window *window = m_context->m_window;
    
    while (window->getRenderWindow()->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window->setDone();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left)
                {
                    m_direction = -1;
                    m_pressingLeft = true;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    m_direction = 1;
                    m_pressingRight = true;
                }
                if (event.key.code == sf::Keyboard::Up)
                    m_pressingUp = true;
                if (event.key.code == sf::Keyboard::Space)
                    m_context->m_entityHandler->getPlayer()->jump();
                if (event.key.code == sf::Keyboard::LShift)
                {
                    int direction = 0;
                    if (m_direction < 0 && m_pressingUp)
                        direction = 4;
                    else if (m_direction > 0 && m_pressingUp)
                        direction = 5;
                    else if (m_pressingUp)
                        direction = 3;
                    else if (m_direction > 0)
                        direction = 2;
                    else if (m_direction < 0)
                        direction = 1;
                    if (m_context->m_entityHandler->getPlayer()->dash(direction))
                        m_context->m_window->shake();
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left)
                {
                    m_direction = 0;
                    m_pressingLeft = false;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    m_direction = 0;
                    m_pressingRight = false;
                }
                if (event.key.code == sf::Keyboard::Up)
                    m_pressingUp = false;
                break;
            default:
                break;
        }
    }
    
    m_context->m_entityHandler->getPlayer()->setDirection(0);
    if (m_pressingLeft)
        m_context->m_entityHandler->getPlayer()->setDirection(-1);
    else if (m_pressingRight)
        m_context->m_entityHandler->getPlayer()->setDirection(1);
}
