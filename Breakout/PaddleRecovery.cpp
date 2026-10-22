#include "PaddleRecovery.h"
#include "Paddle.h"
#include "PaddleIdle.h"

PaddleRecovery::PaddleRecovery(float duration)
{
	_recoveryDuration = duration;
}

void PaddleRecovery::OnEnter(Paddle* paddle)
{
	paddle->setColour(sf::Color(128, 128, 128, 255));
}

void PaddleRecovery::OnExit(Paddle* paddle)
{
}

void PaddleRecovery::OnUpdate(Paddle* paddle, float dt)
{
	_recoveryDuration -= dt;
	if (_recoveryDuration <= 0)
	{
		paddle->setState(new PaddleIdle());
	}
}
