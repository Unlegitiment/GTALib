#pragma once
class CGameState {
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;
};