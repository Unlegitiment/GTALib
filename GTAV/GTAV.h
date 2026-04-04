#pragma once
#include "scriptmanagement/scriptctrl.h"
#include "world/world.h"
#include "ui/HudMgr.h"
#include "log.h"
class GTA {
public:
	using DeathHandler = bool(*)(void*);
	static void Init() {
		gtaInfof("-- GTA Begin Init -- \n\n");
		ScriptThreadController::Init();
		CWorldMgr::Init();
		CFader::Init();
		legit::netLogger::Send("\n");
		gtaInfof("-- GTA End Init  -- \n\n");
	}
	static void Update() {
		ScriptThreadController::Update();
		CWorldMgr::Update();
		CFader::Update();
		if (sm_pDeathHandler && DeathHandlerArgs) {
			if (!HasHandledDeath) {
				HasHandledDeath = sm_pDeathHandler(DeathHandlerArgs);
			}
			if (!PED::IS_PED_DEAD_OR_DYING(CWorldMgr::GetWorld()->GetPlayerPedId(), 1)) {
				HasHandledDeath = true;
			}
		}
	}
	static void SetDeathHandler(DeathHandler pfnSignal, void* ArgumentsToBeSentUponDeath) {
		sm_pDeathHandler = pfnSignal;
		DeathHandlerArgs = ArgumentsToBeSentUponDeath;
	}
	static void SetDeathArgs(void* UpdateToArgs) {
		DeathHandlerArgs = UpdateToArgs;
	}
	static void ResetDeathHandler() {
		sm_pDeathHandler = nullptr;
		DeathHandlerArgs = 0;
		HasHandledDeath = true;
	}
	static void Shutdown() {
		CFader::Shutdown();
		CWorldMgr::Shutdown();
	}
private:
	
	static inline bool HasHandledDeath = false;
	static inline void* DeathHandlerArgs = nullptr;
	static inline DeathHandler sm_pDeathHandler = nullptr;
};