#include "InputHandler.hpp"
#include "SharedContext.h"
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
        std::cout << "test" << std::endl;
        switch(event.type)
        {
            case sf::Event::Closed:
                window->setDone();
                break;
            default:
                break;
        }
    }
}
