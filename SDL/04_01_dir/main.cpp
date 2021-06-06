#include <iostream>
#include <SDL.h>
#include "Game.h"


const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main()
{
    std::cout << "game init attempt...\n";
    if (TheGame::Instance()->init("Chapter 3: Working with Game Objects",
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  640, 480, SDL_WINDOW_SHOWN))
    {
        std::cout << "game init success!\n";

        Uint32 frameStart, frameTime;

        while (TheGame::Instance()->running())
        {
            frameStart = SDL_GetTicks();

            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));   
            }
        }

        std::cout << "game closing...\n";    
        TheGame::Instance()->clean();
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    return 0;
}

