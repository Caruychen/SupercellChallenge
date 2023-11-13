#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "InputHandler.h"
#include "Player.h"
#include "resources/Resources.h"
#include "Rectangle.h"
#include "Coin.h"
#include "Door.h"

Game::Game() :
    m_state(State::WAITING),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayer(std::make_unique<Player>(this)),
    m_pDoor(std::make_unique<Door>(this)),
    m_score(0),
    m_clearedLevels(0)
{
    
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
}

Game::~Game()
{
    
}

bool Game::initialise(sf::Vector2f pitchSize)
{
    m_pClock->restart();
    std::string assetPath = Resources::getAssetPath();
    if (!m_font.loadFromFile(assetPath + "Lavigne.ttf"))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }

    //Initialize shapes from TileMap
    resetLevel(MapArray1);
    return true;
}

void Game::resetLevel(const int* tileMap)
{
    m_pCoins.clear();
    m_pRectangles.clear();

    m_pPlayer->setIsDead(false);
    m_pDoor->setTriggered(false);

    const sf::Vector2f tileSize(TileSizeX, TileSizeY);

    for (int y = 0; y < GridSize; y++)
    {
        for (int x = 0; x < GridSize; x++)
        {
            int i = x + y * GridSize;

            const sf::Vector2f worldPos = sf::Vector2f(x * tileSize.x, y * tileSize.y);
            switch (tileMap[i])
            {
                case    eTile::eCoin:
                    m_pCoins.push_back(std::make_unique<Coin>(CoinRadius, worldPos));
                    break;
                case    eTile::eBlock:
                    m_pRectangles.push_back(std::make_unique<Rectangle>(tileSize, worldPos));
                    break;
                case    eTile::ePlayerSpawn :
                    m_pPlayer->setPosition(worldPos);
                    break;
                case    eTile::eDoor :
                    m_pDoor->setPosition(worldPos);
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
            if (m_pClock->getElapsedTime().asSeconds() >= 3.f)
            {
                m_state = State::ACTIVE;
            }
        }
        break;
            
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->updatePhysics(deltaTime);
            m_pPlayer->update(deltaTime);

            if (m_pPlayer->isDead())
                resetLevel(MapArray1);
                
            if (m_pDoor->isTriggered())
            {
                m_clearedLevels++;
                if (m_clearedLevels == LevelCount)
                {
                    m_clearedLevels = 0;
                    m_score = 0;
                    m_state = State::WAITING;
                    m_pClock->restart();
                    resetLevel(MapArray1);
                }
                else
                {
                    resetLevel(MapArray2);
                }
                
            }
        }
        break;
    }
    int i = 0;
    while (i < m_pCoins.size())
    {
        if (m_pCoins[i]->getCollected())
        {
            std::swap(m_pCoins[i], m_pCoins.back());
            m_pCoins.pop_back();
            continue;
        }
        i++;
    }

    
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //  Draw texts.
    if (m_state == State::WAITING)
    {
        sf::Text startText;
        startText.setFont(m_font);
        startText.setString("Game Start!");
        startText.setFillColor(sf::Color::White);
        startText.setPosition(80.0f, 80.0f);
        startText.setStyle(sf::Text::Bold);
        target.draw(startText);
    }
    else
    {
        sf::Text coinText;
        coinText.setFont(m_font);
        coinText.setFillColor(sf::Color::White);
        coinText.setStyle(sf::Text::Bold);
        coinText.setString(std::to_string(m_pPlayer->getCoins()));
        coinText.setColor(sf::Color::Yellow);
        coinText.setPosition(sf::Vector2f(ScreenWidth - coinText.getLocalBounds().getSize().x, 0));
        target.draw(coinText);
    }

    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
    for (auto& temp : m_pCoins)
    {
        temp->draw(target, states);
    }
    for (auto& temp : m_pRectangles)
    {
        temp->draw(target, states);
    }

    m_pDoor->draw(target, states);
}


void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}

std::vector<Coin*> Game::getCoins()
{
    std::vector<Coin*> pCoins;

    for (auto& temp : m_pCoins)
    {
        pCoins.push_back(temp.get());
    }
    return pCoins;
}

std::vector<Rectangle*> Game::getRectangles() const
{
    std::vector<Rectangle*> pRectangles;

    for (auto& pRectangle : m_pRectangles)
    {
        pRectangles.push_back(pRectangle.get());
    }
    return (pRectangles);
}

Door* Game::getDoor()
{
    return m_pDoor.get();
}
