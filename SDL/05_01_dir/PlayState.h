#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include "GameState.h"
#include "SDLGameObject.h"
#include <vector>

class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_playID; }

private:

    static const std::string s_playID;

    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

    std::vector<GameObject*> m_gameObjects;
};

#endif

