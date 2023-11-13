#include "InputHandler.h"
#include "SharedContext.h"
#include "EntityHandler.h"
#include "Window.h"
#include <iostream>

InputHandler::InputHandler(SharedContext *context) :
    m_context(context)
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
                    m_context->m_entityHandler->getPlayer()->setDirection(-1);
                else if (event.key.code == sf::Keyboard::Right)
                {
                    std::cout << "rightdown" << std::endl;
                    m_context->m_entityHandler->getPlayer()->setDirection(1);
                }
                if (event.key.code == sf::Keyboard::Space)
                    m_context->m_entityHandler->getPlayer()->jump();
                if (event.key.code == sf::Keyboard::LShift)
                {
                    if (m_context->m_entityHandler->getPlayer()->dash())
                        m_context->m_window->shake();
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left)
                    m_context->m_entityHandler->getPlayer()->setDirection(0);
                if (event.key.code == sf::Keyboard::Right)
                {
                    std::cout << "rightup" << std::endl;
                    m_context->m_entityHandler->getPlayer()->setDirection(0);
                }
                break;
            default:
                break;
        }
    }
}
