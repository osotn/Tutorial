#include "InputHandler.h"
#include "Game.h"
#include <iostream>

void InputHandler::initialiseJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    if (SDL_NumJoysticks() > 0)
    {
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            
            if (joy != NULL) {
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));

                std::vector<bool> tempButtons;

                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
                    tempButtons.push_back(false);

                m_buttonStates.push_back(tempButtons);

                std::cout << "Opened Joystick " << i <<
                             " Name: " << SDL_JoystickNameForIndex(i) <<
                             " Number of Axes: " <<  SDL_JoystickNumAxes(joy) <<
                             " Number of Buttons: " << SDL_JoystickNumButtons(joy) <<
                             " Number of Balls: " <<  SDL_JoystickNumBalls(joy) << 
                             " Number of Hats: " << SDL_JoystickNumHats(joy) << std::endl;
            }
            else {
                std::cout << SDL_GetError();
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;

        std::cout << "Initialised " << m_joysticks.size() << " joystick(s)" << std::endl;
    }
    else
    {
        m_bJoysticksInitialised = false;
    }

    for (int i = 0; i < 3; i++)
        m_mouseButtonStates.push_back(false);
}

void InputHandler::clean()
{
    if (! m_bJoysticksInitialised)
        return;

    for (int i = 0; i < SDL_NumJoysticks(); i++)
        SDL_JoystickClose(m_joysticks[i]);
}

void InputHandler::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        m_keystates = SDL_GetKeyboardState(0);

        if (event.type == SDL_QUIT)
            TheGame::Instance()->quit();

        if(event.type == SDL_JOYAXISMOTION) {
            int whichOne = (int) event.jaxis.which;

            if (event.jaxis.axis == 0) {
                if (event.jaxis.value > m_joystickDeadZone)
                    m_joystickValues[whichOne].first->setX(1);
                else if (event.jaxis.value < -m_joystickDeadZone)
                    m_joystickValues[whichOne].first->setX(-1);
                else
                    m_joystickValues[whichOne].first->setX(0);
            }

            if (event.jaxis.axis == 1) {
                if (event.jaxis.value > m_joystickDeadZone)
                    m_joystickValues[whichOne].first->setY(1);
                else if (event.jaxis.value < -m_joystickDeadZone)
                    m_joystickValues[whichOne].first->setY(-1);
                else
                    m_joystickValues[whichOne].first->setY(0);
            }

            if (event.jaxis.axis == 2) {
                if (event.jaxis.value > m_joystickDeadZone)
                    m_joystickValues[whichOne].second->setX(1);
                else if (event.jaxis.value < -m_joystickDeadZone)
                    m_joystickValues[whichOne].second->setX(-1);
                else
                    m_joystickValues[whichOne].second->setX(0);
            }

            if (event.jaxis.axis == 5) {
                if (event.jaxis.value > m_joystickDeadZone)
                    m_joystickValues[whichOne].second->setY(1);
                else if (event.jaxis.value < -m_joystickDeadZone)
                    m_joystickValues[whichOne].second->setY(-1);
                else
                    m_joystickValues[whichOne].second->setY(0);
            }


            if ((int)event.jaxis.axis <= 5)
            std::cout << "joy axis motion, which =  " << (int) event.jaxis.which <<
                         "axis num = " << (unsigned) event.jaxis.axis <<
                         "value = " << (signed) event.jaxis.value << std::endl;
        }

        if (event.type == SDL_JOYBUTTONDOWN) {
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = true;
            std::cout << "button  " << (int) event.jbutton.button << " DOWN" << std::endl;
        }

        if (event.type == SDL_JOYBUTTONUP) {
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = false;
            std::cout << "button  " << (int) event.jbutton.button << " UP" << std::endl;
        }

        if(event.type == SDL_JOYHATMOTION) {
            std::cout << "joy hat motion, which =  " << (int) event.jhat.which <<
                         "hat num = " << (unsigned) event.jhat.hat <<
                         "value = " << (signed) event.jhat.value << std::endl;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {

            std::cout << "Mouse button  " << (int) event.button.button << " DOWN" << std::endl;

            if (event.button.button == SDL_BUTTON_LEFT)
                m_mouseButtonStates[LEFT] = true;

            if (event.button.button == SDL_BUTTON_MIDDLE)
                m_mouseButtonStates[MIDDLE] = true;

            if (event.button.button == SDL_BUTTON_RIGHT)
                m_mouseButtonStates[RIGHT] = true;
        }

        if (event.type == SDL_MOUSEBUTTONUP) {

            std::cout << "Mouse button  " << (int) event.button.button << " UP" << std::endl;

            if (event.button.button == SDL_BUTTON_LEFT)
                m_mouseButtonStates[LEFT] = false;

            if (event.button.button == SDL_BUTTON_MIDDLE)
                m_mouseButtonStates[MIDDLE] = false;

            if (event.button.button == SDL_BUTTON_RIGHT)
                m_mouseButtonStates[RIGHT] = false;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            m_mousePosition.setX(event.motion.x);
            m_mousePosition.setY(event.motion.y);

            std::cout << "Mouse motion: x = " << event.motion.x << " y = " << event.motion.y << std::endl;
        }
    }
}

int InputHandler::xvalue(int joy, int stick)
{
    if ((unsigned)joy >= m_joystickValues.size())
        return 0;

    if (stick == 1)
        return m_joystickValues[joy].first->getX();

    if (stick == 2)
        return m_joystickValues[joy].second->getX();

    return 0; 
}

int InputHandler::yvalue(int joy, int stick)
{
    if ((unsigned)joy >= m_joystickValues.size())
        return 0;

    if (stick == 1)
        return m_joystickValues[joy].first->getY();

    if (stick == 2)
        return m_joystickValues[joy].second->getY();

    return 0; 
}

void InputHandler::reset()
{
    for (int i = 0; i < 3; i++)
        m_mouseButtonStates.push_back(false);
}

