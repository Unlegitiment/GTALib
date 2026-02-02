#pragma once
#include <ModCore/logger/netLog.h>
#include <ModCore/terminalColor.h>
#include <ModCore/math/Point.h>
#include <ModCore/math/Vector2.h>
#include <ModCore/math/Color.h>
#include <Main/keyboard.h>

#include <utility>
#define modInfof(msg, ...) FMT_LOG(RHIBlue "[INFO][MOD][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define modWarnf(msg, ...) FMT_LOG(RYellow "[WARNING][MOD][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define modErrorf(msg, ...) FMT_LOG(RHIRed "[ERROR][MOD][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#include <GTAV/ui/rect/immediate.h>
#include <GTAV/scriptmanagement/scriptctrl.h>
#include <string>
#include <array>
#include <typeinfo>


class PlayerSwitchScaleform {
public:
	PlayerSwitchScaleform() {
		this->Scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("PLAYER_SWITCH");
		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->Scaleform)) { // this is thread blocking. really cringe when you think about it. the alternative is constantly queue operations until we get our buffer back, recursively request (holy shit bad), or my favorite, send an asset request request the assets this script uses all in one, badda bing badda boom, you done. 
			this->Scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("PLAYER_SWITCH");
			WAIT(0);
		}
	}
	void SET_SWITCH_VISIBLE(bool b) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_SWITCH_VISIBLE");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(b);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	void SET_SWITCH_SLOT(int index, int stateEnum, int charEnum, bool selected, const char* pedheadshot_txt_string) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_SWITCH_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(index);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(stateEnum);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(charEnum);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(selected);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(pedheadshot_txt_string);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	void SET_MULTIPLAYER_HEAD(const char* _newTXD) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_MULTIPLAYER_HEAD");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(_newTXD);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

	}
	void SET_SWITCH_HINTED(int index, int hinted) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_SWITCH_HINTED");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(index);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(hinted);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	void SET_SWITCH_HINTED_ALL(bool hinted0, bool hinted1, bool hinted2, bool hinted3) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_SWITCH_HINTED_ALL");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(hinted0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(hinted1);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(hinted2);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(hinted3);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	void SET_PLAYER_DAMAGE(int index, bool bVisible, bool bFlash) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_PLAYER_DAMAGE");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(index);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(bVisible);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(bFlash);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	void SET_SWITCH_COUNTER_ALL(int count0, int count1, int count2, int count3) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_SWITCH_COUNTER_ALL");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(count0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(count1);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(count2);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(count3);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	void SET_PLAYER_SELECTED(int sindex) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_PLAYER_SELECTED");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(sindex);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	void SET_MP_LABEL(const char* str) const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, "SET_MP_LABEL");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(str);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	int GET_SWITCH_SELECTED() {
		throw "not implemented";
	}
	void Debug() const {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(Scaleform, "debug");
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	int GetScaleform() const {
		return this->Scaleform;
	}
	operator int() {
		return Scaleform;
	}
private:
	int Scaleform;
};
class ScaleformCall { // move this to gtav.
public:
	ScaleformCall(int Scalef, bool isDbg = false) : dbg(isDbg) {
		this->ScaleformIndex = Scalef;
		if (isDbg)
			modInfof("Is Debug: %s\n", isDbg ? "TRUE" : "FALSE");
	}

	template<typename... T> void Call(const char* Method, T&&... a) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->ScaleformIndex, Method);
		(CallOp(std::move(a)), ...);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	~ScaleformCall() {
		ScaleformIndex = 0;
	}
protected:
	template<typename T> void CallOp(T&& value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)value);
		if (dbg)
			modInfof("Casting and pushing under an integer. This is likely for enums! Type: %s\n", typeid(T).name());
	}
	template<> void CallOp<char const []>(char const(&& value)[]) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(value);
		if (dbg) {
			modInfof("Pushing a string literal\n");
		}
	}
	template<> void CallOp<int>(int&& value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)value);
		if (dbg)
			modInfof("Pushing an integer\n");
	}
	template<> void CallOp<const char*>(const char*&& value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(value);
		if (dbg) {
			modInfof("Pushing a constant string\n");
		}
	}
	template<> void CallOp<bool>(bool&& value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(value);
		if (dbg)
			modInfof("Pushing a bool\n");

	}
	template<> void CallOp<float>(float&& value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(value);
		if (dbg)
			modInfof("Pushing a float\n");

	}
	template<> void CallOp<char*>(char*&& value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(value);
		if (dbg)
			modInfof("Pushing a PlayerName string.\n");
	}
	bool dbg = false;
	int ScaleformIndex = 0;
};

enum class CharAvailability {
	NONE,
	AVAILABLE,
	UNAVAILABLE,
	NOTMET,
};
enum class CharImage {
	MICHAEL,
	FRANKLIN,
	TREVOR,
	MP
};
enum CharSelector {
	TREVOR,
	FRANKLIN,
	ONLINE,
	MICHAEL,
};
struct sCharacterInfo {
	sCharacterInfo() = default;
	sCharacterInfo(CharSelector selector, CharImage Image) {
		this->Selector = selector;
		this->Image = Image;
		this->Availability = CharAvailability::UNAVAILABLE;
		IsHinted = false;
		IsDamaged = false;
		IsDamagedFlashing = false;
		Counter = 0;
	}
	CharSelector Selector;
	CharImage Image;
	CharAvailability Availability;
	bool IsHinted;
	bool IsDamaged;
	bool IsDamagedFlashing;
	int Counter;
};
struct sMPInfo : public sCharacterInfo {
	sMPInfo() : sCharacterInfo(CharSelector::ONLINE, CharImage::MP){
		StatusString = std::string();
	}
	std::string StatusString;
};
class CSelectorController {
public:
	enum class eCharacter {
		FRANKLIN,
		MICHAEL,
		TREVOR
	};
	CSelectorController() {
		m_MainCharacters[0] = sCharacterInfo(CharSelector::FRANKLIN, CharImage::FRANKLIN);
		m_MainCharacters[1] = sCharacterInfo(CharSelector::MICHAEL, CharImage::MICHAEL);
		m_MainCharacters[2] = sCharacterInfo(CharSelector::TREVOR, CharImage::TREVOR);
		this->m_SelectorMP = sMPInfo();
		modInfof("Successfully inited.\n");
	}
	void SetMPCharacterInfo(sMPInfo value) {
		m_SelectorMP = value;
	}
	void SetCharacterInfo(int Selector, sCharacterInfo info) {
		if (Selector == CharSelector::ONLINE) {
			modErrorf("This is the wrong function use, %s\n", "SetMPCharacterInfo");
			return;
		}
		if (Selector > m_MainCharacters.size()) {
			modErrorf("Cannot set a value that is higher than the Character's array size.\n");
			return;
		}
		m_MainCharacters[Selector] = info;
	}
	void Show() {
		m_bIsBeingDisplayed = true;
	}
	bool IsDisplaying() const {
		return m_bIsBeingDisplayed;
	}
	void Hide() {
		m_bIsBeingDisplayed = false;
	}
	void SetSelector(CharSelector selector) {
		this->m_iSelected = selector;
	}
	sCharacterInfo* GetCharacterInfo(int Index) {
		if (Index > this->m_MainCharacters.size()) {
			modErrorf("Cannot set a value that is higher than the size of the array.\n");
			return nullptr;
		}
		if (Index == 3) {
			modErrorf("Value is equal to the Online Character. Please do not use this function for that.\n");
			return nullptr;
		}
		return &this->m_MainCharacters[Index];
	}
	sMPInfo& GetMultiplayerInfo() {
		return this->m_SelectorMP;
	}
	void Update() {
		if (!m_bIsBeingDisplayed) return;
		ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_SWITCH_VISIBLE", false);
		for (int i = 0; i < m_MainCharacters.size(); i++) {
			sCharacterInfo& op = m_MainCharacters[i];
			ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_SWITCH_SLOT", op.Selector, op.Availability, op.Image, m_iSelected == op.Selector, (const char*)"");
			if (op.IsDamaged) {
				ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_PLAYER_DAMAGE", op.Selector, op.IsDamaged, op.IsDamagedFlashing);
			}
		}
		ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_SWITCH_COUNTER_ALL", m_MainCharacters[2].Counter, m_MainCharacters[0].Counter, m_SelectorMP.Counter, m_MainCharacters[1].Counter);  // trevor, franklin, online, michael
		ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_SWITCH_HINTED_ALL", m_MainCharacters[2].IsHinted, m_MainCharacters[0].IsHinted, m_SelectorMP.IsHinted, m_MainCharacters[1].IsHinted);
		if (!this->m_SelectorMP.StatusString.empty()) {
			m_SelectorMP.Availability = CharAvailability::NONE;
			ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_MP_LABEL", this->m_SelectorMP.StatusString.c_str());
		}
		ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_SWITCH_SLOT", m_SelectorMP.Selector, m_SelectorMP.Availability, m_SelectorMP.Image, m_iSelected == CharSelector::ONLINE, (const char*)"");
		ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_PLAYER_SELECTED", this->m_iSelected);
		ScaleformCall(m_Scaleform.GetScaleform(), 0).Call("SET_SWITCH_VISIBLE", true);

		float fAspectRatio = GRAPHICS::GET_SCREEN_ASPECT_RATIO();
		float fSize = 0.180;
		GRAPHICS::DRAW_SCALEFORM_MOVIE(m_Scaleform, 0.927, 0.899, fSize / fAspectRatio, fSize * (fAspectRatio - (fAspectRatio - 1)), 255, 255, 255, 255, 0);
	}
	~CSelectorController() {

	}
	PlayerSwitchScaleform& GetScaleform() {
		return this->m_Scaleform;
	}
private:
	bool m_bIsBeingDisplayed = false;
	int m_iSelected = 0;
	PlayerSwitchScaleform m_Scaleform{};
	sMPInfo m_SelectorMP;
	std::array<sCharacterInfo, 3> m_MainCharacters;
};

class CPlayerSwitch {
public:
	static void Init() { // this is not technically a gtav layer.
		Selector = new CSelectorController();
		Selector->Show();

		Selector->GetCharacterInfo(0)->Availability = CharAvailability::AVAILABLE;
		Selector->GetCharacterInfo(1)->Availability = CharAvailability::AVAILABLE;
		Selector->GetCharacterInfo(2)->Availability = CharAvailability::AVAILABLE; 

		if (Selector->GetCharacterInfo(0)->Selector == CharSelector::FRANKLIN) {
			modInfof("Franklin\n");
			Selector->GetCharacterInfo(0)->Counter = 1;
			Selector->GetCharacterInfo(0)->IsHinted = 1;
		}
		if (Selector->GetCharacterInfo(1)->Selector == CharSelector::MICHAEL) {
			modInfof("Michael\n");
			Selector->GetCharacterInfo(1)->Counter = 2;
		}
		if (Selector->GetCharacterInfo(2)->Selector == CharSelector::TREVOR) {
			modInfof("Trevor\n");
			Selector->GetCharacterInfo(2)->Counter = 3;
		}
		//Michael->Counter = 1;
		//Michael->IsDamaged = 1;
		//Michael->Availability = CharAvailability::AVAILABLE;
		//Michael->IsDamagedFlashing = 1;
		//Selector->SetSelector(Michael->Selector);
		Selector->SetSelector(CharSelector::TREVOR);
		sMPInfo& info = Selector->GetMultiplayerInfo();
		info.StatusString = "Hello!";
	}
	enum GamePadConstants {
		DPADUP = 8,
		DPADDOWN = 9,
		DPADLEFT = 10,
		DPADRIGHT = 11,
		FRONTEND_CONTEXT_BUTTON = 20,
		FRONTEND_OPTIONS_BUTTON = 21,
		NO_BUTTON_PRESSED = 9999,
		LEFTSHOULDER1 = 4,
		LEFTSHOULDER2 = 5,
		RIGHTSHOULDER1 = 6,
		RIGHTSHOULDER2 = 7,
		START = 12,
		SELECT = 13,
		SQUARE = 14,
		TRIANGLE = 15,
		CROSS = 16,
		CIRCLE = 17,
		LEFTSHOCK = 18,
		RIGHTSHOCK = 19,
	};
	static void Update() {
		Selector->Update();
		if (IsKeyJustUp(VK_SUBTRACT)) {
			if (sm_bIsMenuActive == false) {
				sm_bIsMenuActive = true;
				Hash h = MISC::GET_HASH_KEY("FE_MENU_VERSION_SP_PAUSE");
				HUD::ACTIVATE_FRONTEND_MENU(h, false, 8);
				modInfof("activating frontend\n");
			}
			else {
				sm_bIsMenuActive = false;
				modInfof("closing frontend\n");
				HUD::SET_FRONTEND_ACTIVE(0);
			}
		}
		if (!sm_bIsMenuActive) return;
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_HEADING_DETAILS");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("Str1");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("Str2");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("Str3");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(1); // all this flag does is captialize the first string.
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_HEADER_TITLE");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("title"); // -- title of game/mission/activity.
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(0); // does nothing -- vertified? 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("description"); // description.
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(0); // is challenge? again does nothing?
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SHIFT_CORONA_DESC");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(1); // bump up to allow for description to show (From SET_HEADER_TITLE)
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(1); // Hides the tab markers. 
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_MENU_HEADER_TEXT_BY_INDEX");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1); // each menu would likely have unique shit here. (index of element does not control page content.)
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("label"); // what to set the tab value to. 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1); // controls the length of the tab (very useful for customly built menus) 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1); // controls the capitialization of the "Label" string.
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_MENU_ITEM_COLOUR");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1); // index again.
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(116); // color enum, hud colors.
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("LOCK_MENU_ITEM");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(2); // index again.
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1); // locked? this one is weird, does not block viewing of that page, but sets a locked icon next to it and grays it out.
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_MENU_ITEM_ALERT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(3); // index again.
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("WARNING STRING"); // rather interesting. likely meant to be combined with SET_MENU_HEADER_TEXT_BY_INDEX, specifically the length of the tab. 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(116); // not sure what effect this has. in dump its listed as "col" but in game has no effect on SP_PAUSE.
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		//GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_ALL_HIGHLIGHTS"); // sets the color for all tabs.
		//GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(3); // all highlights. likely a bool.
		//GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(116); // color.
		//GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		//GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("HIGHLIGHT_MENU");
		//GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(4); // sets the tab highlight to specifically be that one, disregards other inputs.
		//GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		//So im still not sure how to access the title?
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_TITLE");
		for (int i = 0; i < 10; i++) {
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(i);
		}
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();



		int colId = 1;
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DATA_SLOT");
		//Specific to the PAGE upon setupColumns, these values are initialized.
		//In the case of PAUSE_MENU_PAGES_MAP column Id 0 is a "mapLegend" and columnId 1 is freemodeDetails.
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(colId); // columnId 0 -- constant. Is not sent to the data effectively removed from the equation once addDataToView ->GUIView::addItem-> {this.dataList[i] = _dataArray} dataArray being all of the stuff we provide below.
		//PauseMenuBaseItem::function set data(_d)
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // index 0 -- In FREEMODE_DETAILS this controls the column we are looking at. 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // menuId 1
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // Unique Id 2 -- Defined By the Item's "function set data(_d)" method tells us which functionality we are looking at. 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(3); // type 3
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(2); // initialIndex 4
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // isSelectable 5
		//SLICE(6)
		// 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("Player Beat your Score."); // Text Left 0 
		//NON-GENERIC TERRITORY FreemodeDetailsItem -- This is controlled by the TYPE parameter up there.
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("EnderPlayzz"); // PlayerName Right 1 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("<*0RSG"); // CrewTag 2 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // SC Icon Visible

		//NON-GENERIC TERRITORY FreemodeDetailsItem
		//GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("Hello2"); // Text Right 1
		//GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(23); // IconMCTarget 2 -- Found in mp_mission_details_card.ytd -- gametype_icons
		//GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(112); // HudColor 3
		//GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0); // ShowCheck 4
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("DISPLAY_DATA_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(colId); // columnId 0 
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

	}
	static void Shutdown() {
		delete Selector;
	}
private:
	static inline bool sm_bIsMenuActive = false;
	static inline CSelectorController* Selector = nullptr;
};
class CMod {
public:
	static void Init() {
		modInfof("--Mod Init Begin--\n\n");

		CPlayerSwitch::Init();

		::Logger::Write("\n");
		modInfof("--Mod Init End  --\n\n");
		float fAspectRatio = GRAPHICS::GET_SCREEN_ASPECT_RATIO();
		modInfof("Aspect Ratio: %f\n", fAspectRatio);
	}
	static void Update() {
		CPlayerSwitch::Update();
		if (IsKeyJustUp(VK_NUMPAD0)) {
			for (const auto& a : ScriptThreadController::GetSet()) {
				modInfof("Script %d(%s) is in Set.\n", a, SCRIPT::GET_NAME_OF_SCRIPT_WITH_THIS_ID(a));
			}
		}
	}
	static void Shutdown() {
		CPlayerSwitch::Shutdown();
	}
private:
};