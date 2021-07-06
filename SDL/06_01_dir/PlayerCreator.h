#ifndef __PLAYER_CREATOR_H__
#define __PLAYER_CREATOR_H__

#include "BaseCreator.h"
#include "Player.h"

class PlayerCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new Player();
    }
};

#endif

