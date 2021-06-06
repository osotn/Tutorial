#ifndef __InputHandler__
#define __InputHandler__

#include <SDL.h>
#include <vector>

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        static InputHandler* s_pInstance = 0;

        if (s_pInstance == 0)
            s_pInstance = new InputHandler();

        return s_pInstance;
    }

    void update();
    void clean();

    void initialiseJoysticks();

    bool joysticsInitialised() { return m_bJoysticksInitialised; }
    
private:

    InputHandler() {}
    ~InputHandler() {}
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialised;

};

typedef InputHandler TheInputHandler;

#endif

