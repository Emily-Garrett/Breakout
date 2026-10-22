#include "PaddleParry.h"
#include "Paddle.h"
#include "PaddleIdle.h"
#include "PaddleRecovery.h"

PaddleParry::PaddleParry()
{
	_parryDuration = 0.1f;
}

void PaddleParry::OnEnter(Paddle* paddle)
{
	paddle->setCanParry(true);
	paddle->setColour(sf::Color::Yellow);
}

void PaddleParry::OnExit(Paddle* paddle)
{
	paddle->setCanParry(false);
}

void PaddleParry::OnUpdate(Paddle* paddle, float dt)
{
	_parryDuration -= dt;
	if (_parryDuration <= 0)
	{
		paddle->setState(new PaddleRecovery(0.3f));
	}
}