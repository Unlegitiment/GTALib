#pragma once
#include "Freemode.h"
#include "../Gameplay.h"
#include <Project - The End\Game\Gamemode\Flow.h>
class CGlobals {
public:
	void Init() {

	}
	void Update() {
		sm_bStartFreemode = IsFreemodeStartConditionTriggered();
		if (sm_bStartFreemode) {
			ActivateMultiplayer();
		}
	}
	void ActivateMultiplayer() {
		if (sm_FreemodeInstance) CGameplay::GetFlow()->SetGamemode(nullptr);
		sm_FreemodeInstance = new CFM();
	}
	bool IsFreemodeStartConditionTriggered() {
		bool isMarkerUsed = false;// CGameplay::GetFreemodeLauncher()->IsMarkerTriggered();
		return isMarkerUsed;
	}
private:
	static inline CFM* sm_FreemodeInstance = nullptr;
	static inline bool sm_bStartFreemode = false;
};