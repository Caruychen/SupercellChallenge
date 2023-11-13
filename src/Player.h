#pragma once

#include "Character.h"

class Player: public Character
{
public:
    Player(EntityHandler *handler);
    ~Player();
    
    void handleMovementInput();
    void incrementScore();
    void update();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
private:
    sf::Text m_text;
    unsigned int m_score;
};
