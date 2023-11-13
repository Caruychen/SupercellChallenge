#pragma once

struct SharedContext;

class InputHandler
{
public:
    InputHandler(SharedContext *context);
    ~InputHandler();
    
    void pollEvents(void);
    
private:
    SharedContext *m_context;
};
