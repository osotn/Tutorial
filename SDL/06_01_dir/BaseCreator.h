#ifndef __BASE_CREATOR_H__
#define __BASE_CREATOR_H__

#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator
{
public:

    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

#endif

