#pragma once

class Paddle;

class PaddleState
{
public:
	PaddleState() {};
	virtual void OnEnter(Paddle* paddle) = 0;
	virtual void OnExit(Paddle* paddle) = 0;
	virtual void OnUpdate(Paddle* paddle, float dt) = 0;
};