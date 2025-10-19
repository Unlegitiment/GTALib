#pragma once
#include "Components\HelpText\HelpText.h"
#include "Components\Scaleform\ScaleformManager.h"
class GTAHud {
public:
	static void Init() {
		sm_HelpTextComponent = new CHelpText();
		sm_ScaleformMgr = new CScaleformManager();
	}
	static void Update() {
		GetHelpText()->GetController().Update();
	}
	static CHelpText* GetHelpText() { return sm_HelpTextComponent; }
	static CScaleformManager* GetScaleformMgr() { return sm_ScaleformMgr; }
	static void Shutdown() {
		delete sm_ScaleformMgr;
		delete sm_HelpTextComponent;
	}
private:
	static inline CHelpText* sm_HelpTextComponent = nullptr;
	static inline CScaleformManager* sm_ScaleformMgr = nullptr;
	GTAHud() = default;
};