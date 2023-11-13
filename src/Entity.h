#pragma once

#include <SFML/Graphics.hpp>
#include "CollisionElement.h"

using Collisions = std::vector<CollisionElement>;
class EntityHandler;

class Entity
{
public:
    Entity(
           EntityHandler *handler,
           const sf::Vector2f size,
           const sf::Vector2f maxVelocity,
           const sf::Vector2f maxAcceleration);
    ~Entity();
    
    // Methods
    void move(const float x, const float y);
    void move(sf::Vector2f pos);
    void addVelocity(const float x, const float y);
    void addVelocity(const sf::Vector2f value);
    void accelerate(const float x, const float y);
    void accelerate(const sf::Vector2f value);
    void addFriction(const float deltaSeconds);
    virtual void update();
    
    // Accessors
    void respawn();
    
protected:
    void _updateBox();
    virtual void _checkCollisions();
    virtual void _resolveCollisions();
    
    EntityHandler   *m_handler;
    sf::Vector2f        m_velocity;
    sf::Vector2f        m_acceleration;
    
private:
    const sf::Vector2f  m_size;
    const sf::Vector2f  m_maxVelocity;
    const sf::Vector2f  m_maxAcceleration;
    sf::Vector2f        m_spawnPosition;
    sf::Vector2f        m_position;
    bool                m_isMoving;
    bool                m_collidingX;
    bool                m_collidingY;
    bool                m_collidingYBottom;
    sf::FloatRect       m_box;
    Collisions          m_collisions;
};
