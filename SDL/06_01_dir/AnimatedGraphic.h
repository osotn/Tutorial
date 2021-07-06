#ifndef __ANIMATED_GRAPHIC__
#define __ANIMATED_GRAPHIC__

#include "SDLGameObject.h"
#include "LoaderParams.h"

class AnimatedGraphic: public SDLGameObject
{
public:

    AnimatedGraphic() : SDLGameObject() {}

    virtual void load(const LoaderParams *pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif

