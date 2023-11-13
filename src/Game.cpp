#include "Game.h"
#include "Window.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "resources/Resources.h"

Game::Game()
{}

Game::~Game()
{}

bool Game::initialise()
{
    std::string assetPath = Resources::getAssetPath();
    if (!m_font.loadFromFile(assetPath + "Lavigne.ttf"))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }
    m_window.create();
    return true;
}

void Game::update()
{
    m_window.update();
}

void Game::render()
{
    m_window.beginDraw();
    m_window.endDraw();
}

void Game::restartClock()
{
    m_deltaTime = m_clock.restart();
}

bool Game::isRunning() const
{
    return !this->m_window.isDone();
}
