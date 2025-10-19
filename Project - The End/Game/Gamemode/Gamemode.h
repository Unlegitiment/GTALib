#pragma once
#include <functional>
#include "Textures.h"
#include <Project - The End\Game\GameEntities\Markers.h>

CHANNEL_COLOR(GAMEMODE, RHICyan);
#define gamemodeLogf(fmt, ...) __LAG_LOGF__(GAMEMODE, "[GAMEMODE]" fmt, ##__VA_ARGS__)
#define gamemodeWarnf(fmt, ...) __LAG_WARNF__(GAMEMODE, "[GAMEMODE]" fmt, ##__VA_ARGS__)

struct sMinigamePlayerDescription {
	const GamemodeTexture* m_Texture;
	const char* m_GameType;
	const char* m_GameName;
	const char* m_RequiredPlayers;
	bool m_bIsGamemodeRockstarVerified;
	CVector3 m_GamemodePosition;
};
enum eColorSelection {
	PRIMARY,
	SECONDARY,
	ECOLSEL_MAX
};
struct sMiniGameThemeColor {
	union Color {
		Color32 m_Color32;
		Color64 m_Color64;
		int m_HudColor;
	};
	Color m_Colors[eColorSelection::ECOLSEL_MAX];
	sMiniGameThemeColor() : m_Colors{ {},{} } {

	}
};
enum eLauncherSpecsMarkerSelection {
	MARKER_MAIN,
	MARKER_SECONDARY,
	SPEC_MARKER_MAX
};
struct sMinigameLauncherMarkerSpecifications {
	using Specs = sMarkerData;
	Specs m_Markers[SPEC_MARKER_MAX];
	virtual void DefaultSpecs(CVector3 Position, Color32 Color, const char* texture) {
		gamemodeLogf("Default Specs called");
		auto& m_MainMarker = m_Markers[MARKER_MAIN];
		auto& m_SideGlow = m_Markers[MARKER_SECONDARY];
		m_MainMarker.Type = 9;
		m_MainMarker.m_Position = Position;
		m_MainMarker.m_Color = Color; // boo hoo.
		m_MainMarker.m_Scale = CVector3(5, 5, 1); // Scale of Marker is Predetermined. 
		m_MainMarker.m_Dictionary = std::string("mpmissmarkers256");
		m_MainMarker.m_TextureName = texture;
		m_MainMarker.m_DoesFaceCam = 1;
		m_SideGlow.Type = 1;
		m_SideGlow.m_Position = m_MainMarker.m_Position - CVector3(0, 0, 0.2f);
		m_SideGlow.m_Scale = m_MainMarker.m_Scale - CVector3(0.25, 0.25, 0);
		m_SideGlow.m_Color = Color;
	}
};
struct sMinigameDescriptor {
	sMinigameDescriptor() : m_Theme(){
		m_MainMarker = new CMarker();
		m_SideGlow = new CMarker();
	}
	sMinigamePlayerDescription m_Description;
	sMiniGameThemeColor m_Theme;
	sMinigameLauncherMarkerSpecifications m_MarkerSpecifications;
	CMarker* m_MainMarker;
	CMarker* m_SideGlow;
	std::function<void(const sMinigameDescriptor&)> m_DrawFunction = [](const sMinigameDescriptor& GameDescription) {};
	~sMinigameDescriptor() {
		delete m_MainMarker;
		delete m_SideGlow;
	}
};
struct LauncherContext {
	virtual ~LauncherContext() = default;
};
class CGamemode {
public:
	CGamemode() : m_Descriptor() {
		
	}
	virtual void Launch(const LauncherContext* ctx) {

	}
	virtual void Init() {

	}
	virtual void Update() {

	}
	virtual void Shutdown() {

	}
	virtual ~CGamemode() {
		
	}
	const sMinigameDescriptor& GetDescriptionConst() const {
		return m_Descriptor;
	}
	sMinigameDescriptor& GetDescription() {
		return this->m_Descriptor;
	}
protected:
private:
	sMinigameDescriptor m_Descriptor;
};
