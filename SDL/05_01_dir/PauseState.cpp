#include "PauseState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include "InputHandler.h"
#include <iostream>

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
    unsigned cObjects = m_gameObjects.size();

    for(unsigned i = 0; i < cObjects; i++)
    {
        if(cObjects == m_gameObjects.size()){
            m_gameObjects[i]->update();
        }
    }
}

void PauseState::render()
{
    for (unsigned i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter()
{
    if (!TheTextureManager::Instance()->load("assets/resume.png", "resumebutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* button1 = new MenuButton(new LoaderParams(200, 100, 200, 80, "mainbutton"), s_pauseToMain);
    GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "resumebutton"), s_resumePlay);

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::onExit()
{
    for (unsigned i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    //m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
    TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();

    std::cout << "exiting PauseState\n";
    return true;
}

void PauseState::s_pauseToMain()
{
    std::cout << "Pause button clicked\n";
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay()
{
    std::cout << "Resume button clicked\n";
    TheGame::Instance()->getStateMachine()->popState();
}

