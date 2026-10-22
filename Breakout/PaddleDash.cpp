#include "PaddleDash.h"
#include "Paddle.h"
#include "PaddleRecovery.h"

PaddleDash::PaddleDash(float movingRight)
{
	_movingRight = movingRight;
	_duration = 0.3f;
	_speed = 800.f;
}

void PaddleDash::OnEnter(Paddle* paddle)
{
	paddle->setColour(sf::Color::Blue);
}

void PaddleDash::OnExit(Paddle* paddle)
{
}

void PaddleDash::OnUpdate(Paddle* paddle, float dt)
{
	_duration -= dt;
	if (_duration <= 0)
	{
		paddle->setState(new PaddleRecovery(0.1f));
	}

	_movingRight ? paddle->moveRight(PADDLE_DASH_SPEED, dt) : paddle->moveLeft(PADDLE_DASH_SPEED, dt);
}