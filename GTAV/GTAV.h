#pragma once
#include "scriptmanagement/scriptctrl.h"
#include "log.h"
class GTA {
public:
	static void Init() {
		gtaInfof("-- GTA Begin Init -- \n\n");
		ScriptThreadController::Init();


		::Logger::Write("\n");
		gtaInfof("-- GTA End Init  -- \n\n");
	}
	static void Update() {
		ScriptThreadController::Update();
	}
	static void Shutdown() {

	}
private:

};