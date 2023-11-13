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
    int m_direction;
    bool m_pressingUp;
    bool m_pressingLeft;
    bool m_pressingRight;
};
