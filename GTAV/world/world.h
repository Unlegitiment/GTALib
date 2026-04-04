#pragma once
#include <ModCore/thirdparty/ScriptHook/include/natives.h>
struct Time {
	Time() = default;
	Time(int iHour, int iMinute, int iSecond) : Hour(iHour), Minute(iMinute), Second(iSecond){

	}
	int Hour, Minute, Second;
};
class CTimeController {
public:
	void Update() {

	}
	Time GetFrozenTime() const {
		return this->m_FrozenTime;
	}
	void SetTime(Time t) {
		CLOCK::SET_CLOCK_TIME(t.Hour, t.Minute, t.Second);
	}
	void AdvanceTo(Time t) {
		CLOCK::ADVANCE_CLOCK_TIME_TO(t.Hour, t.Minute, t.Second); // THIS does not do what I wanted it to do, so fuck you RSG.
	}
	void FreezeTimeAt(Time t) {
		m_bIsTimeFrozen = true;
		m_FrozenTime = t;
		SetTime(t);
		CLOCK::PAUSE_CLOCK(true);
	}
	Time GetCurrent() {
		return Time(CLOCK::GET_CLOCK_HOURS(), CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
	}
	void FreezeTimeAtCurrent() {
		FreezeTimeAt(GetCurrent());
	}
	void UnfreezeTime() {
		m_bIsTimeFrozen = false;
		CLOCK::PAUSE_CLOCK(false);
	}
private:
	Time m_FrozenTime;
	bool m_bIsTimeFrozen = false;
};
class CWeatherController {
public:
	void Update() {

	}
	void SetWeatherNow() {

	}
private:

};
class CWorld {
public:
	int GetPlayerPedId() {
		return PLAYER::PLAYER_PED_ID();
	}
	bool IsBlackoutActive() const {
		return m_bIsBlackoutActive;
	}
	bool DoesBlackoutAffectVehicles() const {
		return m_bBlackoutAffectsVehicles;
	}
	void SetBlackoutState(bool bPersistent) {
		this->m_bIsBlackoutActive = bPersistent;
	}
	void SetBlackoutAffectsVehicles(bool bPersistent) {
		this->m_bBlackoutAffectsVehicles = bPersistent;
	}
	void Update() {
		GRAPHICS::SET_ARTIFICIAL_LIGHTS_STATE(m_bIsBlackoutActive);
		GRAPHICS::SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE(m_bBlackoutAffectsVehicles);
		m_TimeController.Update();
		PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(this->m_fPedDensityThisFrame);
		this->m_fPedDensityThisFrame = 1.f; // whatever default is. Idk.
	}
	CTimeController& GetTimeController() {
		return m_TimeController;
	}
	void SetTime(Time t) {
		m_TimeController.SetTime(t);
	}
	void FreezeTimeAt(Time t) {
		m_TimeController.FreezeTimeAt(t);
	}
	void FreezeTimeAtCurrent() {
		m_TimeController.FreezeTimeAtCurrent();
	}
	void UnfreezeTime() {
		m_TimeController.UnfreezeTime();
	}
	void SetPedDensityThisFrame(float fNormal) {
		this->m_fPedDensityThisFrame = fNormal;
	}
	float GetPedDensityThisFrame() const {
		return this->m_fPedDensityThisFrame;
	}
private:
	float m_fPedDensityThisFrame = 0;
	bool m_bBlackoutAffectsVehicles = false;
	bool m_bIsBlackoutActive = false;
	CTimeController m_TimeController{};
	CWeatherController m_WeatherController{};
};
class CWorldMgr {
public:
	static void Init() {
		sm_pWorld = new CWorld();
	}
	static CWorld* GetWorld() {
		return sm_pWorld;
	}
	static CTimeController* GetTimeController() { 
		if (!sm_pWorld) return nullptr;
		return &sm_pWorld->GetTimeController();
	}
	static void Update() {
		sm_pWorld->Update();
	}
	static void Shutdown() {
		delete sm_pWorld;
	}
private:
	static inline CWorld* sm_pWorld = nullptr;
};