#ifndef __InputHandler__
#define __InputHandler__

#include <SDL.h>
#include <vector>
#include <utility>
#include "Vector2D.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

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

    bool joysticksInitialised() { return m_bJoysticksInitialised; }

    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

    bool getButtonState(int joy, int buttonNumber)
    {
        return m_buttonStates[joy][buttonNumber];
    }

    bool getMouseButtonState(int buttonNumber) {
        return m_mouseButtonStates[buttonNumber];
    }

    Vector2D* getMousePosition()
    {
        return &m_mousePosition;
    }

    bool isKeyDown(SDL_Scancode key)
    {
        if (m_keystates)
            return (m_keystates[key] == 1);
        
         return false;
    }

private:

    InputHandler() {}
    ~InputHandler() {}
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialised;

    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    std::vector<bool> m_mouseButtonStates;
    Vector2D m_mousePosition;
    const Uint8* m_keystates;

    const int m_joystickDeadZone = 10000;
};

typedef InputHandler TheInputHandler;

#endif

