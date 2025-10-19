#pragma once
#include <Project - The End\Game\Gamemode\Gamemode.h>
class CMultiplayerListener {
public:
	CMultiplayerListener() {

	}
	void Update() {

	}
private:

};
class CGamemodeSingleplayer : public CGamemode {
public:
	CGamemodeSingleplayer() {

	}
	void Init() {

	}
	void Update() {
		m_Listener->Update();
	}
	void Shutdown() {

	}
private:
	CMultiplayerListener* m_Listener = nullptr;
};