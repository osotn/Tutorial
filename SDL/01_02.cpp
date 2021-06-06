#include <SDL.h>

bool g_bRunning = false;

SDL_Window * g_pWindow = 0;
SDL_Renderer * g_pRenderer = 0;

bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{

    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

        if(g_pWindow != 0)
        {
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);


            if (g_pRenderer != 0)
            {
                SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

void render()
{
    SDL_RenderClear(g_pRenderer);
    SDL_RenderPresent(g_pRenderer);
}

void update()
{
}

void clear()
{
    SDL_DestroyWindow(g_pWindow);
    SDL_DestroyRenderer(g_pRenderer);
    SDL_Quit();
}

void handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                g_bRunning = false;
            break;

            default:
            break;
        }
    }
}

int main()
{
    if(init("Chapter 1: Setting up SDL",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            640, 480, SDL_WINDOW_SHOWN))
    {
        g_bRunning = true;
    }
    else
    {
        return 1;
    }

    while (g_bRunning)
    {
        handleEvents();
        update();
        render();
    }

    clear();

    return 0;
}

