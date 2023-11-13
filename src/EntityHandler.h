#pragma once


struct SharedContext;

class EntityHandler
{
public:
    EntityHandler(SharedContext *context);
    ~EntityHandler();
    
    SharedContext *getContext();
    
private:
    SharedContext *m_context;
};
