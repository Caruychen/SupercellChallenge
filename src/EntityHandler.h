#pragma once

#include "Player.h"

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
    
    void setPlayerPos(const sf::Vector2f &position);
    SharedContext *getContext();
    Player *getPlayer();
    
private:
    SharedContext   *m_context;
    Player          m_player;
};
