#include "GamemodeMgr.h"
#include <Project - The Game\SHV\natives.h>
#include <Project - The Game\Hud.h>
#include <Project - The End\Game\Gamemode\Flow.h>
#include <Project - The End\Game\Gameplay.h>
void CGamemodeMgr::AddGamemode(CGamemode* gm) {
	m_Games.push_back(gm);
}

void CGamemodeMgr::Update() {
	if (m_CurrentGamemode) {
		return;
	}
	for (auto& gm : m_Games) {
		if (gm->GetDescriptionConst().m_Description.m_GamemodePosition.Dist(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1)) < gm->GetDescriptionConst().m_MarkerSpecifications.m_Markers[MARKER_SECONDARY].m_Scale.GetX()) {
			int Ped = PLAYER::PLAYER_PED_ID();
			bool PlayerInVehicle = PED::IS_PED_IN_ANY_VEHICLE(Ped, 0);
			bool PlayerIsDead = PED::IS_PED_DEAD_OR_DYING(Ped, 1);
			if (PlayerInVehicle) {
				if (!GTAHud::GetHelpText()->GetController().IsDisplayActive()) {
					GTAHud::GetHelpText()->GetController().ChangeText("You must trigger this job on-foot.");
					GTAHud::GetHelpText()->GetController().ActivateDisplay(0);
				}
			}
			else if (PlayerIsDead) {
				if (GTAHud::GetHelpText()->GetController().IsDisplayActive()) {
					GTAHud::GetHelpText()->GetController().DeactivateDisplay();
				}
			}
			else {
				if ((!GTAHud::GetHelpText()->GetController().IsDisplayActive())) {
					GTAHud::GetHelpText()->GetController().ChangeText("Press  ~INPUT_CONTEXT~ to enter this job.");
					GTAHud::GetHelpText()->GetController().ActivateDisplay(0);
				}
				if (PAD::IS_CONTROL_JUST_RELEASED(0, 51)) {
					CGameplay::GetFlow()->SetGamemode(gm);
					m_CurrentGamemode = gm;
				}
			}

		}
	}
}

CGamemode* CGamemodeMgr::GetGM(const sMinigamePlayerDescription& desc) {
	for (auto& gm : m_Games) {
		if (gm->GetDescriptionConst().m_Description.m_GameName == desc.m_GameName) {
			return gm;
		}
	}
}

const std::vector<CGamemode*>& CGamemodeMgr::GetModesConst() const {
	return this->m_Games;
}

std::vector<CGamemode*>& CGamemodeMgr::GetModes() {
	return this->m_Games;
}

void CGamemodeMgr::RemoveGamemode(CGamemode* gm) {
	auto res = std::find(m_Games.begin(), m_Games.end(), gm);
	if (res == m_Games.end()) {
		return;
	}
	m_Games.erase(res);
	if (m_CurrentGamemode == gm) {
		CGameplay::GetFlow()->SetGamemode(nullptr);
	}
}
