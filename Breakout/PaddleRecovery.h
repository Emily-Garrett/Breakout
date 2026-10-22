#pragma once

#include "PaddleState.h"

class PaddleRecovery : public PaddleState
{
public:
	PaddleRecovery(float duration);
	virtual void OnEnter(Paddle* paddle) override;
	virtual void OnExit(Paddle* paddle) override;
	virtual void OnUpdate(Paddle* paddle, float dt) override;
private:
	float _recoveryDuration;
};