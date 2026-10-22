#pragma once

#include "PaddleState.h"

class PaddleIdle : public PaddleState
{
public:
	PaddleIdle();
	virtual void OnEnter(Paddle* paddle) override;
	virtual void OnExit(Paddle* paddle) override;
	virtual void OnUpdate(Paddle* paddle, float dt) override;
};