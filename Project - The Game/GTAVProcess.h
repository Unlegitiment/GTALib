#pragma once
#include "../Project - The Framework/Watchers/ApplicationWatcher.h"
#include "GameScript.h"
#include "../Project - The End/Logging/EndLogger.h"
#include "Hud.h"
#include "Game\Player\Switch\PlayerSwitch.h"
class GTAV {
public:
	static void Init() {
		GameScripts::Init();
		GTAHud::Init();
		sm_SwitchMgr = new CPlayerSwitchMgr();
	}
	static CPlayerSwitchMgr* GetSwitchMgr() { return sm_SwitchMgr; }
	static void Update() {
		GameScripts::Update();
		GTAHud::Update();
		sm_SwitchMgr->Update();
	}
	static void Shutdown() {
		delete sm_SwitchMgr;
		GTAHud::Shutdown();
		GameScripts::Shutdown();
	}
private:
	static inline CPlayerSwitchMgr* sm_SwitchMgr = nullptr;
	GTAV() = default;
};