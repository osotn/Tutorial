#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);

    m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

    handleInput();
    SDLGameObject::update();
}

void Player::clean()
{
}

void Player::handleInput()
{
    if (TheInputHandler::Instance()->joysticksInitialised())
    {
        m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0,1));
        m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0,1));
    }

    Vector2D * vec = TheInputHandler::Instance()->getMousePosition();
    m_velocity = (*vec - m_position) / 50;

#if 0
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
        m_velocity.setX(2);

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
        m_velocity.setX(-2);

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
        m_velocity.setY(-2);

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
        m_velocity.setY(2);
#endif
}   

