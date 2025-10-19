#pragma once
#include <Project - The End\Logging\EndLogger.h>
class Renderer;
class CTransitionManager;
class CGameFlow;
class CTransitionTest;
class CMarkerMgr;
class CGamemode;
class CGamemodeMgr;
#include "Marker\MarkerRet.h"
struct sGameplayMarker {
	MarkerReturn m_Marker[2];
};
#include <Project - The End\Debug\DbgModule.h>
#include <Project - The Game\Components\Scaleform\ScaleformManager.h>

class CGameplayDebugTest : public IDebugClass{
public:
	CGameplayDebugTest();
	void Update() override;
	~CGameplayDebugTest();
private:
	CGamemode* m_Gamemode = nullptr;
	CScaleform* m_GamemodeScaleform = nullptr;
};
class CGameplay {
public:
	static constexpr float MARKER_STATS_VISIBLITY_RANGE = 10.f;
	static void Init();
	static void AddGamemode(CGamemode* gamemode);
	static CTransitionManager* GetTransitionManager();
	static Renderer* GetRenderer();
	static CGameFlow* GetFlow();
	static CMarkerMgr* GetMarkerMgr();
	static void Update();
	static void Shutdown();
private:
	static void ShouldSpecialMarkerBeActive(bool b);
	static void SetupSpecialMarker();
	static inline CGameplayDebugTest* sm_pDebugSandbox;
	static inline sGameplayMarker* sm_pSpecialMarker = nullptr;
	static inline CMarkerMgr* sm_pMarkerMgr = nullptr;
	static inline Renderer* sm_pRenderer = nullptr;
	static inline CTransitionManager* sm_pMgr = nullptr;
	static inline bool sm_bShouldSpecialMarkerDisplay = true;
	static inline bool sm_bDoesMarkerNeedToBeAdded = true;
	//static inline CTransitionTest* sm_pTransTest = nullptr;
	static inline CGameFlow* sm_pGameFlow = nullptr;
};
CHANNEL_COLOR(GAMEPLAY, RCyan);
#define gameplayLogf(fmt, ...) __LAG_LOGF__(GAMEPLAY, "[GAMEPLAY]" fmt, __VA_ARGS__)
#define gameplayWarnf(fmt, ...) __LAG_WARNF__(GAMEPLAY, "[GAMEPLAY]" fmt, __VA_ARGS__)