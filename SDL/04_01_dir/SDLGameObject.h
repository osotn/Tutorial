#ifndef __SDLGameObject__
#define __SDLGameObject__

#include <SDL.h>
#include <string>
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject: public GameObject
{
public:

    SDLGameObject(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

protected:

    std::string m_textureID;

    int m_currentFrame;
    int m_currentRow;

    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;

    SDL_RendererFlip m_flip;
};

#endif

