#include <iostream>
#include <SDL.h>
#include "Game.h"

int main()
{
    std::cout << "game init attempt...\n";
    if (TheGame::Instance()->init("Chapter 3: Working with Game Objects",
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  640, 480, SDL_WINDOW_SHOWN))
    {
        std::cout << "game init success!\n";
        while (TheGame::Instance()->running())
        {
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();
            SDL_Delay(10); // add the delay
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

