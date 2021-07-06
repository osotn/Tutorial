#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:

    Player() : SDLGameObject() {}

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams *pParams);

private:
    void handleInput();
};

#endif

