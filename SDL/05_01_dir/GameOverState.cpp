#include "GameOverState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "AnimatedGraphic.h"
#include <iostream>

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
    unsigned cObjects = m_gameObjects.size();

    for(unsigned i = 0; i < cObjects; i++)
    {
        if(cObjects == m_gameObjects.size()){
            m_gameObjects[i]->update();
        }
    }
}

void GameOverState::render()
{
    for (unsigned i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool GameOverState::onEnter()
{
    if (!TheTextureManager::Instance()->load("assets/gameover.png", "gameovertext", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/restart.png", "restartbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameovertext"), 2);
    GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);
    GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "entering GameOverState\n";
    return true;
}

bool GameOverState::onExit()
{
    for (unsigned i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    //m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
    TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
    TheTextureManager::Instance()->clearFromTextureMap("restartbutton");

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();

    std::cout << "exiting GameOverState\n";
    return true;
}

void GameOverState::s_gameOverToMain()
{
    std::cout << "GameOverToMain button clicked\n";
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay()
{
    std::cout << "Restart button clicked\n";
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

