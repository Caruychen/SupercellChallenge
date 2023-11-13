#include "EntityHandler.h"
#include "SharedContext.h"
#include "Window.h"
#include "Map.h"

EntityHandler::EntityHandler(SharedContext *context) :
m_context(context),
m_player(this)
{
    m_context->m_entityHandler = this;
}

EntityHandler::~EntityHandler()
{}

void EntityHandler::update()
{
    m_player.handleMovementInput();
    m_player.update();
    for (Coin &coin: m_coins)
        coin.update();
    for (MovingHazard &hazard: m_movingHazards)
        hazard.update();
}

void EntityHandler::draw()
{
    Window *window = m_context->m_window;
    
    window->draw(m_player);
    for (Coin &coin: m_coins)
        window->draw(coin);
    for (MovingHazard &hazard: m_movingHazards)
        window->draw(hazard);
}

void EntityHandler::progressPlayer()
{
    sf::Vector2f next = m_context->m_map->getNextSpawn();
    setPlayerPos(next);
    m_context->m_window->shiftViewUp();
}

void EntityHandler::incrementPlayerScore()
{
    m_player.incrementScore();
}

void EntityHandler::initPlayerFont()
{
    m_player.init();
}

SharedContext *EntityHandler::getContext()
{
    return m_context;
}

Player *EntityHandler::getPlayer()
{
    return &m_player;
}

void EntityHandler::setPlayerPos(const sf::Vector2f &position)
{
    m_player.setSpawnPosition(position);
    m_player.setPosition(position);
}

void EntityHandler::setCoins(const std::vector<sf::Vector2f> positions)
{
    for (sf::Vector2f pos: positions)
        m_coins.push_back(Coin(this, pos));
}

void EntityHandler::setMovingHazards(const std::vector<MovingHazardData> data)
{
    for (MovingHazardData d: data)
        m_movingHazards.push_back(MovingHazard(
                                               this,
                                               d.m_position,
                                               d.m_horizontal,
                                               d.m_initialDirection
                                               ));
}
