#pragma once
#include "Gamemode.h"
#include <Project - The End\Game\Gameplay.h>
#include <Project - The End\Transition\Transition.h>
class CGameFlow {
public:
	void Update() {
		switch (m_State) {
		case FLOW_DEFAULT_GAMEMODE_UPDATE:
		default:
			if (FLOW_TIMEOUT_START + FLOW_TIMEOUT_MAX >= FLOW_TIMEOUT_END) {
				// we've got a problem! our game is not loading. 
				gameplayLogf("[FLOW]: GameFlow timeout max reached. Attempting to Quick Transition");
				CGameplay::GetTransitionManager()->End(PLAYER::PLAYER_PED_ID());
				m_Gamemode = nullptr;
			}
			if (m_Gamemode) {
				m_Gamemode->Update();
			}
		}
	}
	void SetGamemode(CGamemode* m) {
		if (m_Gamemode) {
			CGameplay::GetTransitionManager()->Begin(PLAYER::PLAYER_PED_ID()); // Shutdown
			m_Gamemode->Shutdown();
			gameplayLogf("[FLOW]: Gameflow trigger shutdown, Gamemode Name: ", m_Gamemode->GetDescriptionConst().m_Description.m_GameName);
		}
		m_Gamemode = m;
		FLOW_TIMEOUT_START = MISC::GET_GAME_TIMER();
		FLOW_TIMEOUT_END = FLOW_TIMEOUT_START + FLOW_TIMEOUT_MAX;
		if (m_Gamemode) {
			if(!CGameplay::GetTransitionManager()->IsTransitionActive()) CGameplay::GetTransitionManager()->Begin(PLAYER::PLAYER_PED_ID());
			gameplayLogf("[FLOW]: Gameflow trigger start, gamemode specified is 0x%p (%s).", m, m->GetDescriptionConst().m_Description.m_GameName);
			m_Gamemode->Init();
			CGameplay::GetTransitionManager()->End(PLAYER::PLAYER_PED_ID());
		}
	}
	CGamemode* GetGamemode() {
		return this->m_Gamemode;
	}
private:
	enum eGameflowState : int{
		FLOW_DEFAULT_GAMEMODE_UPDATE,
	} m_State;
	int FLOW_TIMEOUT_START = 0;
	int FLOW_TIMEOUT_END = 0;
	int FLOW_TIMEOUT_MAX = 25000; // 25 seconds?
	CGamemode* m_Gamemode = nullptr;
	
};