#pragma once

#include "PaddleState.h"

class PaddleParry : public PaddleState
{
public:
	PaddleParry();
	virtual void OnEnter(Paddle* paddle) override;
	virtual void OnExit(Paddle* paddle) override;
	virtual void OnUpdate(Paddle* paddle, float dt) override;
private:
	float _parryDuration;
};