#ifndef __SDLGameObject__
#define __SDLGameObject__

#include <SDL.h>
#include <string>
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject: public GameObject
{
public:

    SDLGameObject() : GameObject() {}

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams *pParams);

    Vector2D& getPosition() { return m_position; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }

protected:

    std::string m_textureID;

    int m_currentFrame;
    int m_currentRow;
    int m_numFrames;

    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;

    void (*m_callback)();
    int m_animSpeed;

    SDL_RendererFlip m_flip;
};

#endif

