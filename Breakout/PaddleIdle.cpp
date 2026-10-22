#include "PaddleIdle.h"
#include "PaddleParry.h"
#include "Paddle.h"

PaddleIdle::PaddleIdle()
{
}

void PaddleIdle::OnEnter(Paddle* paddle)
{
    paddle->setColour(sf::Color::Cyan);
}

void PaddleIdle::OnExit(Paddle* paddle)
{
}

void PaddleIdle::OnUpdate(Paddle* paddle, float dt)
{
    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { paddle->moveLeft(dt); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { paddle->moveRight(dt); }

    // parry
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) { paddle->setState(new PaddleParry()); }
}
