#ifndef __MENU_BUTTON_CREATOR_H__
#define __MENU_BUTTON_CREATOR_H__

#include "BaseCreator.h"
#include "MenuButton.h"

class MenuButtonCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new MenuButton();
    }
};

#endif

