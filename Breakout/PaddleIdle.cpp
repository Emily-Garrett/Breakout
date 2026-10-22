#include "PaddleIdle.h"
#include "Paddle.h"
#include "PaddleParry.h"
#include "PaddleDash.h"

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { paddle->moveLeft(PADDLE_SPEED, dt); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { paddle->moveRight(PADDLE_SPEED, dt); }

    // dash
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) != sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
    {
        paddle->setState(new PaddleDash(sf::Keyboard::isKeyPressed(sf::Keyboard::D)));
    }
    // parry
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) 
    { 
        paddle->setState(new PaddleParry()); 
    }
}
