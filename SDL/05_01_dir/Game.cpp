#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

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

    m_gameObjects.push_back(new Player(new LoaderParams(0, 0, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(0, 100, 128, 82, "animate")));

    TheInputHandler::Instance()->initialiseJoysticks();

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());    
    
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

//    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
//    {
//        m_gameObjects[i]->draw();
//    }

    m_pGameStateMachine->render();

    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
//    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
//    {
//        m_gameObjects[i]->update();
//    }

    m_pGameStateMachine->update();
}

void Game::clean()
{
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
}

void Game::quit()
{
    m_bRunning = false;
}

