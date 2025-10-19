#pragma once
#include "Gamemode.h"
class CGamemodeMgr {
public:
	void AddGamemode(CGamemode* gm);
	void Update();
	CGamemode* GetGM(const sMinigamePlayerDescription& desc);
	const std::vector<CGamemode*>& GetModesConst() const;
	std::vector<CGamemode*>& GetModes();
	void RemoveGamemode(CGamemode* gm);
	bool IsPlayerConditionsMet() {
		bool isPlayerInVehicle = false;
	}
private:
	std::vector<CGamemode*> m_Games;
	CGamemode* m_CurrentGamemode = nullptr;
};