#pragma once

class SharedContext;

class InputHandler
{
public:
    InputHandler(SharedContext *context);
    ~InputHandler();
    
    void pollEvents(void);
    
private:
    SharedContext *m_context;
};
