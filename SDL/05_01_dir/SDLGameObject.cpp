#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams),
    m_position(pParams->getX(), pParams->getY()), m_velocity(0,0), m_acceleration(0,0)
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 1;
    m_currentFrame = 1;

    m_flip = SDL_FLIP_NONE;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_flip);
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;

    //if (m_position.getX() > 600.0) m_position.setX(0); 
    //if (m_position.getY() > 400.0) m_position.setY(0); 

    m_flip = (m_velocity.getX() > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void SDLGameObject::clean()
{
}

