#pragma once
#include "GameState.h"
#include <Project - The Game\SHV\natives.h>
#include <Project - The Game\GTAVProcess.h>
class CTransitionState {
public:
	enum eState {
		PROCESS_TRIGGERED_CURRENT_EXIT,
		PROCESS_AWAITING_CLOUD_DEFAULT_HEIGHT,
		PROCESS_BEGIN_NEXT_STATE,
		PROCESS_IDLE,
	};
	CTransitionState(CGameState* curGameState) : m_CurrentState(curGameState) {};
	void BeginTransition(CGameState* ToTarget) {
		m_NextState = ToTarget;
		m_State = PROCESS_TRIGGERED_CURRENT_EXIT;
	}
	void Update() {
		switch (m_State) {
		case PROCESS_TRIGGERED_CURRENT_EXIT:
			m_CurrentState->Exit();
			PerformTransitionBegin();
			m_State = PROCESS_AWAITING_CLOUD_DEFAULT_HEIGHT;
			break;
		case PROCESS_AWAITING_CLOUD_DEFAULT_HEIGHT:
			if (GTAV::GetSwitchMgr()->GetSwitchState() == this->DEFAULT_STATE) {
				m_State = PROCESS_BEGIN_NEXT_STATE;
			}
			break;
		case PROCESS_BEGIN_NEXT_STATE:
			m_CurrentState = m_NextState;;
			m_NextState = nullptr;
			m_NextState->Enter();
			m_State = PROCESS_IDLE;
			break;
		case PROCESS_IDLE:
		default:
			m_CurrentState->Update();
		}
	}
private:
	void PerformTransitionBegin() {
		sPlayerSwitchData m_Data = sPlayerSwitchData();
		m_Data.m_FromPed = PLAYER::PLAYER_PED_ID();
		m_Data.m_Flags = (eSwitchFlags)0;
		m_Data.m_TargetPed = 0;
		m_Data.m_TargetType = ePlayerSwitchType::EPST_LONG;
		GTAV::GetSwitchMgr()->Start(m_Data);
	}
	CGameState* m_CurrentState = nullptr;
	CGameState* m_NextState = nullptr;
	eState m_State = PROCESS_IDLE;
	static inline constexpr int DEFAULT_STATE = 5;
};