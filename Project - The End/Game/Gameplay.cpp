#include "Gameplay.h"
#include "Renderer\Renderer.h"
#include <Project - The End\Transition\Transition.h>
#include <Project - The End\Transition\TransitionTest.h>
#include "Gamemode/Flow.h"
#include <Project - The End\Debug\Debugger.h>
#include "Marker\MarkerSys.h"
#include <Project - The End\Game\Gamemode\GamemodeMgr.h>
#include <Project - The End\Game\Modes\Freemode.h>
void CGameplay::Init() {
	sm_pMgr = new CTransitionManager();
	sm_pRenderer = new Renderer();
	sm_pGameFlow = new CGameFlow();
	sm_pGameFlow->SetGamemode(nullptr);

	sm_pMarkerMgr = new CMarkerMgr();

	sm_pDebugSandbox = new CGameplayDebugTest();
	Debugger::GetDbgMgr()->Add(sm_pDebugSandbox);

}
void CGameplay::AddGamemode(CGamemode* gm) {

}
CTransitionManager* CGameplay::GetTransitionManager() {
	return sm_pMgr;
}

Renderer* CGameplay::GetRenderer() {
	return sm_pRenderer;
}

CGameFlow* CGameplay::GetFlow() {
	return sm_pGameFlow;
}

CMarkerMgr* CGameplay::GetMarkerMgr() {
	return sm_pMarkerMgr;
}

void CGameplay::Update() {
	sm_pMgr->Update();
	sm_pRenderer->Render();
	sm_pGameFlow->Update();
	sm_pMarkerMgr->Update();
	//sm_pGamemodeMgr->Update();
}

void CGameplay::Shutdown() {
	//sm_pGamemodeMgr->RemoveGamemode(sm_pGamemode);

	//delete sm_pGamemode;
	//delete sm_pGamemodeMgr;

	//sm_pMarkerMgr->Remove(sm_pSpecialMarker->m_Marker[0].m_pMarker);
	//sm_pMarkerMgr->Remove(sm_pSpecialMarker->m_Marker[1].m_pMarker);

	Debugger::GetDbgMgr()->Remove(sm_pDebugSandbox);
	delete sm_pDebugSandbox;
	delete sm_pSpecialMarker;
	delete sm_pMarkerMgr;
	delete sm_pGameFlow;
	delete sm_pRenderer;
	delete sm_pMgr;
}
#include "Modes\Freemode.h"
#include <Main\keyboard.h>
void CGameplay::ShouldSpecialMarkerBeActive(bool b) {
	CGameplay::sm_bShouldSpecialMarkerDisplay = b;
	if (sm_bShouldSpecialMarkerDisplay) {
		CGameplay::GetMarkerMgr()->AddMarker(sm_pSpecialMarker->m_Marker[0]);
		CGameplay::GetMarkerMgr()->AddMarker(sm_pSpecialMarker->m_Marker[1]);
	} else {
		CGameplay::GetMarkerMgr()->RemoveFromList(sm_pSpecialMarker->m_Marker[0]);
		CGameplay::GetMarkerMgr()->RemoveFromList(sm_pSpecialMarker->m_Marker[1]);
	}
}
void CGameplay::SetupSpecialMarker() {
	auto& m_MainMarker = sm_pSpecialMarker->m_Marker[0].m_pMarker->GetData();
	m_MainMarker.Type = 9;
	m_MainMarker.m_Position = CVector3(428.0806, -976.1284, 29.79);
	m_MainMarker.m_Color = Color32(67, 57, 111, 255); // boo hoo.
	m_MainMarker.m_Scale = CVector3(5, 5, 1); // Scale of Marker is Predetermined. 
	m_MainMarker.m_Dictionary = "mpmissmarkers256";
	m_MainMarker.m_TextureName = GamemodeTexture::CustomIcon.GetName();
	m_MainMarker.m_DoesFaceCam = 1;
	auto& m_SideGlow = sm_pSpecialMarker->m_Marker[1].m_pMarker->GetData();
	m_SideGlow.Type = 1;
	m_SideGlow.m_Position = m_MainMarker.m_Position - CVector3(0, 0, 0.2f);
	m_SideGlow.m_Scale = m_MainMarker.m_Scale - CVector3(0.25, 0.25, 0);
	m_SideGlow.m_Color = m_MainMarker.m_Color;

	sm_pSpecialMarker->m_Marker[1].m_UpdateMarker = [&](CMarker* marker) {
		float fDist = marker->GetData().m_Position.Dist(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1));
		if (fDist <= marker->GetData().m_Scale.GetX() && PAD::IS_CONTROL_JUST_RELEASED(0, 51)) {
			CGameplay::GetFlow()->SetGamemode(new CFM());
		}
		return;
		};
	sm_bDoesMarkerNeedToBeAdded = false;
}


CGameplayDebugTest::CGameplayDebugTest() : IDebugClass() {
	m_Gamemode = new CFM();

	auto& desc = m_Gamemode->GetDescriptionConst().m_Description;
	CGameplay::GetRenderer()->Add(m_Gamemode->GetDescription().m_MainMarker->GetRenderMtl());
	CGameplay::GetRenderer()->Add(m_Gamemode->GetDescription().m_SideGlow->GetRenderMtl());

	//CGameplay::GetRenderer()->Add(m_Gamemode->GetDescription().m_MainMarker->GetRenderMtl());
	//CGameplay::GetRenderer()->Add(m_Gamemode->GetDescription().m_SideGlow->GetRenderMtl());
	m_GamemodeScaleform = GTAHud::GetScaleformMgr()->GetScaleform("MP_MISSION_NAME_FREEMODE");
	m_GamemodeScaleform->BeginMethod("SET_MISSION_INFO")
		.Call(desc.m_GameName)
		.Call(desc.m_GameType)
		.Call("") // player info
		.Call("") // percentage
		.Call("") // dbgvale
		.Call(desc.m_bIsGamemodeRockstarVerified)
		.Call(desc.m_RequiredPlayers)
		.Call("") // rp
		.Call("") // cash
		.Call("") // time
		.FinalizeCall();
}
void Draw(CMarker* m_Data) {
	GRAPHICS::DRAW_MARKER_EX(m_Data->GetData().Type,
		m_Data->GetData().m_Position.GetX(), m_Data->GetData().m_Position.GetY(), m_Data->GetData().m_Position.GetZ(),
		m_Data->GetData().m_Direction.GetX(), m_Data->GetData().m_Direction.GetY(), m_Data->GetData().m_Direction.GetZ(),
		m_Data->GetData().m_Rotation.GetX(), m_Data->GetData().m_Rotation.GetY(), m_Data->GetData().m_Rotation.GetZ(),
		m_Data->GetData().m_Scale.GetX(), m_Data->GetData().m_Scale.GetY(), m_Data->GetData().m_Scale.GetZ(),
		m_Data->GetData().m_Color.GetR(), m_Data->GetData().m_Color.GetG(), m_Data->GetData().m_Color.GetB(), m_Data->GetData().m_Color.GetA(),
		m_Data->GetData().m_DoesBounce, m_Data->GetData().m_DoesFaceCam, m_Data->GetData().RotationOrder, m_Data->GetData().DoesRotate,
		m_Data->GetData().m_Dictionary.empty() ? NULL : m_Data->GetData().m_Dictionary.c_str(),
		m_Data->GetData().m_TextureName.empty() ? NULL : m_Data->GetData().m_TextureName.c_str(),
		m_Data->GetData().DoesInvert, m_Data->GetData().Arg1, m_Data->GetData().Arg2
	);
}
void CGameplayDebugTest::Update() {
	GRAPHICS::DRAW_SCALEFORM_MOVIE_3D_SOLID(m_GamemodeScaleform->GetHandle(),
		m_Gamemode->GetDescriptionConst().m_Description.m_GamemodePosition.GetX(), m_Gamemode->GetDescriptionConst().m_Description.m_GamemodePosition.GetY(), m_Gamemode->GetDescriptionConst().m_Description.m_GamemodePosition.GetZ(),
		0, 0, -CAM::GET_GAMEPLAY_CAM_ROT(0).z,
		2, 2, 1,
		5, 5, 0,
		2
	);
	float fDist = m_Gamemode->GetDescription().m_Description.m_GamemodePosition.Dist(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1));
	if (fDist <= m_Gamemode->GetDescription().m_MarkerSpecifications.m_Markers[1].m_Scale.GetX() / 2.0f)  { // for some reason you needa do this. idk why but the radius is not from the center is prolly repp'd like a box or smth :shrug:
		if (!GTAHud::GetHelpText()->GetController().IsDisplayActive()) {
			GTAHud::GetHelpText()->GetController().ChangeText("Press ~INPUT_CONTEXT~ to enter this job.");
			GTAHud::GetHelpText()->GetController().ActivateDisplay(false);
		}
		if (PAD::IS_CONTROL_JUST_RELEASED(0, 51)) {
			CGameplay::GetFlow()->SetGamemode(m_Gamemode);
		}
	} else {
		if (GTAHud::GetHelpText()->GetController().IsDisplayActive()) {
			GTAHud::GetHelpText()->GetController().DeactivateDisplay();
		}
	}
	if (IsKeyJustUp(VK_F15)) {
		CGameplay::GetFlow()->SetGamemode(nullptr);
	}
}
CGameplayDebugTest::~CGameplayDebugTest() noexcept {
	GTAHud::GetScaleformMgr()->ReleaseScaleform(m_GamemodeScaleform);
	delete m_Gamemode;
}

CTriggerMarker::CTriggerMarker(sMarkerData data) {
	m_Marker->GetData() = data;
	CGameplay::GetRenderer()->Add(m_Marker->GetRenderMtl());
}
