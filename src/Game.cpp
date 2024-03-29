#include "Game.h"
#include "Window.h"
#include "SharedContext.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "resources/Resources.h"

Game::Game() :
    m_window(&m_context),
    m_inputHandler(&m_context),
    m_entityHandler(&m_context),
    m_map(&m_context)
{
    m_context.m_clock = &m_clock;
    m_context.m_deltaTime = &m_deltaTime;
    m_context.m_font = &m_font;
}

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
    m_entityHandler.setPlayerPos(m_map.getNextSpawn());
    m_entityHandler.setCoins(m_map.getCoinPositions());
    m_entityHandler.setMovingHazards(m_map.getMovingHazards());
    m_entityHandler.initPlayerFont();
    restartClock();
    return true;
}

void Game::update()
{
    m_window.update();
    m_inputHandler.pollEvents();
    m_entityHandler.update();
}

void Game::render()
{
    m_window.beginDraw();
    m_map.draw();
    m_entityHandler.draw();
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
