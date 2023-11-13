#pragma once

struct SharedContext;

class EntityHandler
{
public:
    EntityHandler(SharedContext *context);
    ~EntityHandler();
    
private:
    SharedContext *m_context;
};
