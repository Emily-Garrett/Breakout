#pragma once

#include "PaddleState.h"

class PaddleDash : public PaddleState
{
public:
	PaddleDash(float movingRight);
	virtual void OnEnter(Paddle* paddle) override;
	virtual void OnExit(Paddle* paddle) override;
	virtual void OnUpdate(Paddle* paddle, float dt) override;
private:
	bool _movingRight;
	float _duration;
	float _speed;
};