#pragma once
#include <Project - The Framework\math\vec3.h>
#include <Project - The Game\SHV\natives.h>
#include <Project - The End\Logging\EndLogger.h>
CHANNEL_COLOR(SWITCH, RIGreen);
#define switchLogf(fmt, ...) __LAG_LOGF__(SWITCH, "[SWITCH]" fmt, ##__VA_ARGS__)
#define switchWarnf(fmt, ...) __LAG_WARNF__(SWITCH, "[SWITCH]" fmt, ##__VA_ARGS__)
//Source FiveM Docs.
enum ePlayerSwitchType {
	EPST_AUTO = 0,
	EPST_LONG = 1,
	EPST_MEDIUM = 2,
	EPST_SHORT = 3
};
enum eSwitchFlags : int {
	NONE = 0,
	SKIP_INTRO = 1,
	SKIP_OUTRO = 2,
	PAUSE_BEFORE_PAN = 4,
	PAUSE_BEFORE_OUTRO = 8,
	SKIP_PAN = 16,
	UNKNOWN_DEST = 32,
	DESCENT_ONLY = 64,
	START_FROM_CAMPOS = 128,
	PAUSE_BEFORE_ASCENT = 256,
	PAUSE_BEFORE_DESCENT = 512,
	ALLOW_SNIPER_AIM_INTRO = 1024,
	ALLOW_SNIPER_AIM_OUTRO = 2048,
	SKIP_TOP_DESCENT = 4096,
	SUPPRESS_OUTRO_FX = 8192,
	SUPPRESS_INTRO_FX = 16384,
	DELAY_ASCENT_FX = 32768
};
struct sPlayerSwitchData {
	ePlayerSwitchType m_TargetType;
	eSwitchFlags m_Flags;
	int m_FromPed;
	int m_TargetPed;
};
class CPlayerSwitchMgr {
public:
	void Start(sPlayerSwitchData data) {
		m_Data = new sPlayerSwitchData(data);
		ConcreteStart();
	}
	void Update() {
		if (m_bIsSwitchActive) {
			m_CurrentSwitchState = STREAMING::GET_PLAYER_SWITCH_STATE();
			m_iCurrentSwitchType = STREAMING::GET_PLAYER_SWITCH_TYPE();
			m_iCurrentJumpCutIndex = STREAMING::GET_PLAYER_SWITCH_JUMP_CUT_INDEX();
			m_iCurrentInterpOutDuration = STREAMING::GET_PLAYER_SWITCH_INTERP_OUT_DURATION();
			m_iCurrentInterpOutCurrentTime = STREAMING::GET_PLAYER_SWITCH_INTERP_OUT_CURRENT_TIME();
		}
	}
	int GetSwitchState() const {
		return this->m_CurrentSwitchState;
	}
	bool DoesHaveTarget() {
		return m_Data->m_TargetPed != 0;
	}
	void SetDestination(Ped nextPed) {
		if (ENTITY::DOES_ENTITY_EXIST(nextPed)) {
			m_Data->m_TargetPed = nextPed;
			OnTargetAvailable();
		}
		else {
			switchWarnf("Destination is invalid. Ped: %d is not available.", nextPed);
		}
	}
	void ForceStopSwitch() {
		STREAMING::STOP_PLAYER_SWITCH(); // i hate switching. 
	}
	void OnTargetAvailable() {
		STREAMING::SWITCH_TO_MULTI_SECONDPART(m_Data->m_TargetPed);
	}
	~CPlayerSwitchMgr() {
		if (m_Data) delete m_Data;
	}
private:

	void ConcreteStart() {
		if (m_Data->m_TargetPed == 0) {
			STREAMING::SWITCH_TO_MULTI_FIRSTPART(m_Data->m_FromPed, m_Data->m_Flags, m_Data->m_TargetType);
			switchLogf("PlayerSwitch does not have a Target Specified");
		} else {
			STREAMING::START_PLAYER_SWITCH(m_Data->m_FromPed, m_Data->m_TargetPed, m_Data->m_Flags, m_Data->m_TargetType);
			delete m_Data;
			switchLogf("PlayerSwitch has a target.");
		}
		m_bIsSwitchActive = true;
	}
	sPlayerSwitchData* m_Data = nullptr;
	bool m_bIsSwitchActive = false;
	int m_CurrentSwitchState = 0;
	int m_iCurrentSwitchType = 0;
	int m_iCurrentJumpCutIndex = 0;
	int m_iCurrentInterpOutDuration = 0;
	int m_iCurrentInterpOutCurrentTime = 0;
};