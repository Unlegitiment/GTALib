#pragma once
#include <Project - The Game\GTAVProcess.h>
// This is a class that actually encapsulates how to program in C++ OOP. Its not perfect use of it because it has hidden dependacies, but this is how update should be used. 
// Its almost beautiful twin ;_)
class CTransitionManager {
public:
	static constexpr int MAX_HEIGHT_STATE = 5;
	void Begin(Ped m_WarpOut) {
		sPlayerSwitchData m_Data{};
		m_Data.m_Flags = NONE;
		m_Data.m_TargetType = ePlayerSwitchType::EPST_LONG;
		m_Data.m_FromPed = m_WarpOut;
		GTAV::GetSwitchMgr()->Start(m_Data);
		m_IsTransitionActive = true;
		switchLogf("[TRANSITION]: Player is beginning transition");
	}
	void Update() {
		if (!m_IsTransitionActive) return;
		if (m_bAllowDescent && GTAV::GetSwitchMgr()->GetSwitchState() == MAX_HEIGHT_STATE) {
			GTAV::GetSwitchMgr()->SetDestination(m_FinalWarpPed);
			switchLogf("[TRANSITION]: Destination Selected, Moving Camera To Position now");
			m_bAllowDescent = false;
		}
	}
	void End(Ped m_WarpIn) {
		m_FinalWarpPed = m_WarpIn;
		m_bAllowDescent = true;
		switchLogf("[TRANSITION]: Ending the Transition");
	}
	bool IsTransitionActive() { return this->m_IsTransitionActive; }
	bool IsTransitionStateAtHeight() {
		return GTAV::GetSwitchMgr()->GetSwitchState() == MAX_HEIGHT_STATE;
	}
private:
	bool m_IsTransitionActive = false;
	bool m_bAllowDescent = false;
	Ped m_FinalWarpPed = 0;
};