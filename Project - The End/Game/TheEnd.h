#pragma once
#include "../../Project - The Framework/core/applet.h"
#include "../App.h"
#include "Renderer\Renderer.h"
#include "GameEntities\Markers.h"
#include <Project - The Game\GTAVProcess.h>
#include "TempThread\TempThreadMgr.h"
#include <functional>
#include <Main\keyboard.h>
CHANNEL_COLOR(GAMEMODE, RHICyan);
#define gamemodeLogf(fmt, ...) __LAG_LOGF__(GAMEMODE, "[GAMEMODE]" fmt, ##__VA_ARGS__)
#define gamemodeWarnf(fmt, ...) __LAG_WARNF__(GAMEMODE, "[GAMEMODE]" fmt, ##__VA_ARGS__
#include <Project - The End\Transition\TransitionTest.h>
#include <Project - The End\Debug\Debugger.h>
#include "Gameplay.h"
class TheEnd {
private:
	TheEnd()
	{
		Debugger::Init();
		CGameplay::Init();
		fwApplet::Get()->AddUpdate(Update);
	}
	~TheEnd() {
		CGameplay::Shutdown();
		Debugger::Shutdown();
		//m_Renderer.Remove(m_Marker2.GetRenderable());
	}
	//CGamemode m_FreemodeDescriptor;
	//CEndMarker m_Marker2;
	//sMkrUpdate m_UpdateShit;
	bool m_bCanUpdateStarterMarker = true;
public:
	static void Update() {
		TheEnd* const Self = TheEnd::Get();
		Debugger::Update();
		CGameplay::Update();
		//Self->m_UpdateShit.Update();
		CVector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		if (IsKeyJustUp(VK_F14)) {
			GTAV::GetSwitchMgr()->ForceStopSwitch();
		}
		if (IsKeyJustUp(VK_F13)) {
			auto res = GTAHud::GetScaleformMgr()->GetScaleforms();
			for (const auto& [key, val] : res) {
				hudLogf("[ScaleformMgr]: Name: %s (RefCounter: %d) ", key.c_str(), val.RefCounters);
				for (auto* instance : val.References) {
					hudLogf("[ScaleformMgr]: \t Instance: 0x%p \\ Handle: %d", instance, instance->GetHandle());
				}
			}
		}
	}
//Singleton.
public:
	static void Init() {
		sm_pInstance = new TheEnd();
	}
	static TheEnd* Get() {
		return sm_pInstance;
	}
	static void Shutdown() {
		delete sm_pInstance;
	}
private:
	static inline TheEnd* sm_pInstance = nullptr;
};