#pragma once

struct SharedContext;

class Map
{
public:
    Map(SharedContext *context);
    ~Map();
    
private:
    SharedContext *m_context;
};
