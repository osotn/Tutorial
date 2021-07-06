#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_flip = SDL_FLIP_HORIZONTAL;
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);
    InputHandler();
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    SDLGameObject::update();
}

void Enemy::clean()
{
}

void Enemy::InputHandler()
{
    if (TheInputHandler::Instance()->joysticksInitialised())
    {
        m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0,2));
        m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0,2));
    }

    Vector2D * vec = TheInputHandler::Instance()->getMousePosition();
    m_acceleration = (*vec - m_position) / 100;
}

