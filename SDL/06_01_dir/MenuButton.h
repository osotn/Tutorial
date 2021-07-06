#ifndef __MENU_BUTTON__
#define __MENU_BUTTON__

#include "SDLGameObject.h"
#include <vector>

enum button_state
{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class MenuButton : public SDLGameObject
{
public:

    MenuButton() : SDLGameObject() {}
    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

private:

    bool m_bReleased;
};

#endif

