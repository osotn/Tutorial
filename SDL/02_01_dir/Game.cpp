#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{

    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

        if(m_pWindow != 0)
        {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);


            if (m_pRenderer != 0)
            {
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
            }
        }
    }
    else
    {
        return false;
    }

    m_bRunning = true;

    if( ! TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";

    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    TheTextureManager::Instance()->draw("animate", 0, 0, 128, 82, m_pRenderer);
    TheTextureManager::Instance()->drawFrame("animate", 100, 100, 128, 82, 1, m_currentFrame, m_pRenderer);
    TheTextureManager::Instance()->drawFrame("animate", 100, 200, 128, 82, 1, m_currentFrame, m_pRenderer);
    TheTextureManager::Instance()->drawFrame("animate", 300, 200, 128, 82, 1, m_currentFrame, m_pRenderer, SDL_FLIP_HORIZONTAL);



    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                m_bRunning = false;
            break;

            default:
            break;
        }
    }
}

