#pragma once

#include "Controller.h"
#include <SFML/Window/Keyboard.hpp>

class Player;
class Game;

struct InputData
{
    bool m_movingUp = true;
    bool m_movingDown = false;
    bool m_movingLeft = false;
    bool m_movingRight = false;

    bool hasInputs() { return m_movingUp || m_movingDown || m_movingLeft || m_movingRight;}
};

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer);
    ~GameInput();
    
    void update(float deltaTime);
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    
    
private:
    InputData m_inputData;
    Game* m_pGame;
    Player* m_pPlayer;
};
