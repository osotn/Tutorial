#ifndef __PAUSE_STATE__
#define __PAUSE_STATE__

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class PauseState : public GameState
{
public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_pauseID; }

private:

    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;

    static void s_pauseToMain();
    static void s_resumePlay();
};

#endif

