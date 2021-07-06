#ifndef __ANIMATED_GRAPHIC_CREATOR_H__
#define __ANIMATED_GRAPHIC_CREATOR_H__

#include "BaseCreator.h"
#include "AnimatedGraphic.h"

class AnimatedGraphicCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};

#endif

