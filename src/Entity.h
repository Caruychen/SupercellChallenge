#pragma once

class EntityHandler;

class Entity
{
public:
    Entity(EntityHandler *handler);
    ~Entity();
    
protected:
    EntityHandler *m_handler;
    
private:
};
