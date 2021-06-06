#include "Player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_velocity.setX(1);
    SDLGameObject::update();
}

void Player::clean()
{
}

