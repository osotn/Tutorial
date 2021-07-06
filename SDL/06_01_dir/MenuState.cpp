#include "MenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include <iostream>
#include "GameObjectFactory.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    unsigned cObjects = m_gameObjects.size();

    for(unsigned i = 0; i < cObjects; i++)
    {
        if(cObjects == m_gameObjects.size()){
            m_gameObjects[i]->update();
        }
    }
}

void MenuState::render()
{
    for (unsigned i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    
    if (!TheTextureManager::Instance()->load("assets/button.png", "playbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/exit.png", "exitbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* button;

    button = TheGameObjectFactory::Instance()->create("MenuButton");
    button->load(new LoaderParams(100, 100, 400, 100, "playbutton", 1, s_menuToPlay));
    m_gameObjects.push_back(button);
    
    button = TheGameObjectFactory::Instance()->create("MenuButton");
    button->load(new LoaderParams(100, 300, 400, 100, "exitbutton", 1, s_exitFromMenu));
    m_gameObjects.push_back(button);
  
    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
    for (unsigned i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    //m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

    std::cout << "exiting MenuState\n";
    return true;
}

void MenuState::s_menuToPlay()
{
    std::cout << "Play button clicked\n";
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
    std::cout << "Exit button clicked\n";
    TheGame::Instance()->quit();
}

