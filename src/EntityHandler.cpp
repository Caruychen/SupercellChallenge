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
}

void EntityHandler::draw()
{
    Window *window = m_context->m_window;
    
    window->draw(m_player);
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

SharedContext *EntityHandler::getContext()
{
    return m_context;
}

void EntityHandler::setPlayerPos(const sf::Vector2f &position)
{
    m_player.setSpawnPosition(position);
    m_player.setPosition(position);
}

Player *EntityHandler::getPlayer()
{
    return &m_player;
}
