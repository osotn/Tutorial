#include "GameOverState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "AnimatedGraphic.h"
#include <iostream>
#include "GameObjectFactory.h"

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

    GameObject* object;

    object = TheGameObjectFactory::Instance()->create("AnimatedGraphic");
    object->load(new LoaderParams(200, 100, 190, 30, "gameovertext", 2, 0, 2));
    m_gameObjects.push_back(object);

    object = TheGameObjectFactory::Instance()->create("MenuButton");
    object->load(new LoaderParams(200, 200, 200, 80, "mainbutton", 1, s_gameOverToMain));
    m_gameObjects.push_back(object);

    object = TheGameObjectFactory::Instance()->create("MenuButton");
    object->load(new LoaderParams(200, 300, 200, 80, "restartbutton", 1, s_restartPlay));
    m_gameObjects.push_back(object);


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

