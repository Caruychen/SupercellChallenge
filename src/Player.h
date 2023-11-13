#pragma once

#include "Rectangle.h"


struct InputData;

class Game;

class Player : public Rectangle
{
public:
    Player(Game* pGame);
    virtual ~Player() {}
    
    bool initialise(){};
    void move(InputData inputData, float deltaTime);
    void updatePhysics(float deltaTime);
    void update(float deltaTime);

    int getCoins() const { return m_coins; };

    bool isDead() const { return m_isDead; }
    void setIsDead(bool isDead) { m_isDead = isDead; }

private:
    bool    m_isGrounded;
    bool    m_isDead = false;
    float   m_jumpTimer = 0.0f;
    Game*   m_pGame;
    int     m_coins = 0;
};
