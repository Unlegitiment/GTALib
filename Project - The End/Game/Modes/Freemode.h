#pragma once
#include "../Gamemode/Gamemode.h"
class CFM : public CGamemode {
public:
	CFM() : CGamemode({}) {

		auto& GameDescription = this->GetDescription().m_Description;
		GameDescription.m_GameType = "~p~Freemode";
		GameDescription.m_RequiredPlayers = "1-30";
		GameDescription.m_bIsGamemodeRockstarVerified = true;
		GameDescription.m_GameName = "GTA Offline";
		GameDescription.m_GamemodePosition = CVector3(428.0806, -976.1284, 29.79);
		GameDescription.m_Texture = &GamemodeTexture::CustomIcon;

		auto& GameTheme = this->GetDescription().m_Theme;
		GameTheme.m_Colors[PRIMARY].m_Color32 = Color32(67, 57, 111, 255);
		GameTheme.m_Colors[SECONDARY].m_Color32 = Color32(190, 180, 220, 255);

		this->GetDescription().m_MarkerSpecifications.DefaultSpecs(GameDescription.m_GamemodePosition, GameTheme.m_Colors[PRIMARY].m_Color32, GamemodeTexture::CustomIcon.GetName());

		this->GetDescription().m_MainMarker->GetData() = this->GetDescription().m_MarkerSpecifications.m_Markers[0];
		this->GetDescription().m_SideGlow->GetData() = this->GetDescription().m_MarkerSpecifications.m_Markers[1];
		gamemodeLogf("Dictionary: %s, Name: %s", GetDescription().m_MainMarker->GetData().m_Dictionary.c_str(), GetDescription().m_MainMarker->GetData().m_TextureName.c_str());
		
	}
	void Init() {
		gamemodeLogf("Init called!");
	}
	void Update() {
		gamemodeLogf("[CFM]::Update()");
	}
	void Shutdown() {
		gamemodeLogf("Shutdown called!");
	}
	~CFM() {
		
	}
private:
};