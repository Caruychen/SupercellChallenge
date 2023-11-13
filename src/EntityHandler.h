#pragma once

#include "Player.h"
#include "Coin.h"
#include "MovingHazard.h"
#include "MovingHazardData.h"

struct SharedContext;

class EntityHandler
{
public:
    EntityHandler(SharedContext *context);
    ~EntityHandler();
    
    void update();
    void draw();
    void progressPlayer();
    void incrementPlayerScore();
    
    SharedContext *getContext();
    Player *getPlayer();
    void setPlayerPos(const sf::Vector2f &position);
    void setCoins(const std::vector<sf::Vector2f> positions);
    void setMovingHazards(const std::vector<MovingHazardData> data);
    
private:
    SharedContext   *m_context;
    Player          m_player;
    std::vector<Coin> m_coins;
    //std::vector<MovingHazard> m_movingHazards;
};
