#include "SDL.h"
#include "AnimatedGraphic.h"

void AnimatedGraphic::load(const LoaderParams *pParam)
{
    SDLGameObject::load(pParam);
}

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
}

