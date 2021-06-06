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
            
            if (joy != NULL)
                m_joysticks.push_back(joy);
            else
                std::cout << SDL_GetError();
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;

        std::cout << "Initialised " << m_joysticks.size() << " joystick(s)" << std::endl;
    }
    else
    {
        m_bJoysticksInitialised = false;
    }
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
        if (event.type == SDL_QUIT)
            TheGame::Instance()->quit();

        if(event.type == SDL_JOYAXISMOTION)
          std::cout << "joy axis motin" << std::endl;

        if (event.type == SDL_JOYBUTTONDOWN)
            std::cout << "button down" << std::endl;

        if (event.type == SDL_JOYBUTTONUP)
            std::cout << "button up" << std::endl;

    }
}

