#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:

    Enemy(const LoaderParams* pParems);
     
    virtual void draw();
    virtual void update();
    virtual void clean();

private:

    void InputHandler();
};

#endif

