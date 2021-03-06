#ifndef __GAME_OVER_STATE__
#define __GAME_OVER_STATE__

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class GameOverState : public GameState
{
public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_gameOverID; }

private:

    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;

    static void s_gameOverToMain();
    static void s_restartPlay();
};

#endif

