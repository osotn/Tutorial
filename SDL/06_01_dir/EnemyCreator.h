#ifndef __ENEMY_CREATOR_H__
#define __ENEMY_CREATOR_H__

#include "BaseCreator.h"
#include "Enemy.h"

class EnemyCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new Enemy();
    }
};

#endif

