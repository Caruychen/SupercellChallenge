#include "EntityHandler.h"
#include "Player.h"
#include "Coin.h"
#include "Constants.h"

Coin::Coin(
           EntityHandler *handler,
           const sf::Vector2f position) :
Entity(handler, sf::Vector2f(CoinRadius * 2, CoinRadius * 2), {0,0}, {0,0}),
m_shape(sf::CircleShape(CoinRadius)),
m_color(sf::Color::Yellow),
m_isCollected(false)
{
    m_shape.setPosition(position);
    m_shape.setFillColor(m_color);
    setSpawnPosition(position);
    setPosition(position);
}

Coin::~Coin()
{}

void Coin::update()
{
    if (m_isCollected)
        return ;
    _checkCollisions();
}

void Coin::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_isCollected)
        return ;
    target.draw(m_shape, states);
}

void Coin::_checkCollisions(void)
{
    Player *player = m_handler->getPlayer();
    if (m_box.intersects(player->getBox()))
    {
        m_isCollected = true;
        player->incrementScore();
    }
}
