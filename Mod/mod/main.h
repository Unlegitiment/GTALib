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
		(CallOp(a), ...);
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
	sMPInfo() : sCharacterInfo(CharSelector::ONLINE, CharImage::MP) {
		StatusString = std::string();
	}
	std::string StatusString;
};
struct Push {
	template<typename... T>
	Push(T&&... args) {
		//modInfof("Push ctor called.\n");
		(CallOp(args), ...);
	}
	Push(const Push&) = delete;
	Push& operator=(const Push&) = delete;
	Push(Push&&) = delete;
	Push& operator=(Push&&) = delete;
private:
	template<typename T> void CallOp(T value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)value);
		//modInfof("Pushing an integer (cast)\n");
	}
	template<size_t S> void CallOp(char const(buffer)[S]) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(buffer);
		//modInfof("Pushing an literal string\n");
	}
	template<> void CallOp<int>(int value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(value);
		//modInfof("Pushing an int\n");
	}
	template<> void CallOp<const char*>(const char* value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(value);
		//modInfof("Pushing an literal string\n");

	}
	template<> void CallOp<bool>(bool value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(value);
		//modInfof("Pushing an bool\n");

	}
	template<> void CallOp<float>(float value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(value);
		//modInfof("Pushing an float\n");

	}
	template<> void CallOp<char*>(char* value) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(value);
		//modInfof("Pushing an char*\n");
	}
};
class CBaseComponent {
public:
	static void SetData(int Column, int Index, int MenuId, int UniqueId, int Type, int InitialIndex, int IsSelectable, const char* LeftMenuItem) {
		Push(Column, Index, MenuId, UniqueId, Type, InitialIndex, IsSelectable, LeftMenuItem);
	}
	static void SetColumnTitle(int Column) {
		Push((int)Column); // might just be visual bug. 
	}

	static void SetColumnFocus(int Column, bool highlighted, int MoveFocus, int prevHighlight) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_COLUMN_FOCUS");
		Push(Column, highlighted, MoveFocus, prevHighlight);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
public:
	static void SetHeaderTitle(const char* Title, int Verified, const char* Description, bool isChallenge) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_HEADER_TITLE");
		Push(Title, Verified, Description, isChallenge);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void SetHeadingDetails(const char* NameString, const char* Date, const char* Money, bool IsNameCaps) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_HEADING_DETAILS");
		Push(NameString, Date, Money, IsNameCaps);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void ShiftCoronaDesc(bool ShiftDesc, bool ShowTabs) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SHIFT_CORONA_DESC");
		Push(ShiftDesc, ShowTabs);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void SetMenuHeaderTextByIndex(int Index, const char* Label, int WidthSpan, bool ForceUpper) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_MENU_HEADER_TEXT_BY_INDEX");
		Push(Index, Label, WidthSpan, ForceUpper);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void SetMenuItemColor(int Index, int HudColor) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_MENU_ITEM_COLOUR");
		Push(Index, HudColor);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void LockMenuItem(int Index, bool IsLocked) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("LOCK_MENU_ITEM");
		Push(Index, IsLocked);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void SetMenuItemAlert(int Index, const char* WarnStr, int Color) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_MENU_ITEM_ALERT");
		Push(Index, WarnStr, Color);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void ScrollMenuInDirection(int Dir) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SCROLL_MENU_IN_DIR");
		Push((int)Dir);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void SetAllHighlights(bool AllHighlights, int Color) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SET_ALL_HIGHLIGHTS");
		Push(AllHighlights, Color);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void ShowMenu(bool b) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER("SHOW_MENU");
		Push((bool)b);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
private:
};
class CFreemodeDetailsComponent : public CBaseComponent {
public:
	/*
		data[0] - nothing?
		data[1] - String
		data[2] - Verified (int)
		data[3] - textureDict (string)
		data[4] - textureName (string)
		data[5] - useTransitionBitmap (only if textureDict is specified else unused)
		data[6] - displayType (FreemodeDetailsDisplayType/int)
		data[7] - if DisplayType is Store it represents the Red channel in RGB.		else specifies the RP Multiplier Text
		data[8] - if DisplayType is Store it represents the Green channel in RGB.	else specifies the CashMultiplier Text
		data[9] - if DisplayType is Store it represents the Blue channel in RGB.	else specifies the APMultiplier Text
		data[10] - if DisplayType is NOT Store it represents the cmMult Text.
	*/
	static void SetColumnTitle(int Column, const char* data0, const char* String, int Verified, const char* textureDict, const char* textureName, bool useTransitionBitmap, int DisplayType, const char* RPorR, const char* CashOrB, const char* APOrG, const char* CmMult) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_COLUMN_TITLE");
		Push(Column, data0, String, Verified, textureDict, textureName, useTransitionBitmap, DisplayType, RPorR, CashOrB, APOrG, CmMult);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	static void SetColumnTitleMission(int Column, const char* data0, const char* String, int Verified, const char* textureDict, const char* textureName, bool useTransitionBitmap, const char* RP, const char* Cash, const char* AP, const char* CM) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_COLUMN_TITLE");
		Push(Column, data0, String, Verified, textureDict, textureName, useTransitionBitmap, 0, RP, Cash, AP, CM);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	// Standard Line of Text. Nothing to write home about.
	static void SetDataSlot1(int Column, int Index, int MenuId, int UniqueId, int InitialIndex, int IsSelectable, const char* LeftMenuItem, const char* RightTextItem) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DATA_SLOT");
		CBaseComponent::SetData(Column, Index, MenuId, UniqueId, 1, InitialIndex, IsSelectable, LeftMenuItem);
		Push((const char*)RightTextItem);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	//Type 2 -- The Default. For most use cases this will be enough. Defines a text entry where the right most holds the activity's logo as well as the ability to set hud colors.
	static void SetDataSlot(int Column, int Index, int MenuId, int UniqueId, int InitialIndex, int IsSelectable, const char* LeftMenuItem, const char* RightTextItem, int Icon, int IconColor, bool IsCheckVisible) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DATA_SLOT");
		CBaseComponent::SetData(Column, Index, MenuId, UniqueId, 2, InitialIndex, IsSelectable, LeftMenuItem);
		Push(RightTextItem, Icon, IconColor, IsCheckVisible);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	//TYPE 3 - Supplies a line with a Player Name as well as their crewtag. SocialClubIcon is also able to be turned on in the case a crewtag is not provided.
	static void SetDataSlot(int Column, int Index, int MenuId, int UniqueId, int InitialIndex, int IsSelectable, const char* LeftMenuItem, const char* RightTextItem, const char* CrewTag, bool IsSocialClubIconVisible) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DATA_SLOT");
		CBaseComponent::SetData(Column, Index, MenuId, UniqueId, 3, InitialIndex, IsSelectable, LeftMenuItem);
		Push(RightTextItem, CrewTag, IsSocialClubIconVisible);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	//Type 4 - Description, This adds a white line above the text
	static void SetDataSlot4(int Column, int Index, int MenuId, int UniqueId, int InitialIndex, int IsSelectable, const char* LeftMenuItem, const char* RightTextItem) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DATA_SLOT");
		CBaseComponent::SetData(Column, Index, MenuId, UniqueId, 4, InitialIndex, IsSelectable, LeftMenuItem);
		Push((const char*)RightTextItem);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	//Type 5 - Description, for longer strings that might need multiple lines, this enables word wrap as well as more complex text features also disables the right Text from being visible.
	static void SetDataSlot5(int Column, int Index, int MenuId, int UniqueId, int InitialIndex, int IsSelectable, const char* LeftMenuItem) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DATA_SLOT");
		CBaseComponent::SetData(Column, Index, MenuId, UniqueId, 5, InitialIndex, IsSelectable, LeftMenuItem);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
};
/*
	Important Scaleforms: These define basically all the important "Base" Types used in the page implementations.
	* pause_menu_header.gfx
	* pause_menu_shared_components.gfx
	* pause_menu_shared_components_02.gfx
	* pause_menu_shared_components_03.gfx
	* pause_menu_shared_components_mp_01.gfx
	* pause_menu_sp_content.gfx
*/
class CInviteMenu {
private:
	template<typename T> static constexpr int U(T&& t) { return static_cast<int>(t); }
	enum class MPIconLabels {
		EMPTY = 0,
		ICON_DATA = 1,
		ICON_DRIVER = 2,
		ICON_HACKER = 3,
		ICON_HIRED_GUN = 4,
		ICON_LEADER = 5,
		ICON_PARACHUTIST = 6,
		ICON_SNIPER = 7,
		INV_CASH_FROM_BANK = 8,
		INV_CASH_FROM_SAFE = 9,
		INV_COKE_DRUGS = 10,
		INV_CUFF_KEYS = 11,
		INV_DOWNLOAD_DATA = 12,
		INV_HEROIN = 13,
		INV_IF_PED_FOLLOWING = 14,
		INV_KEY_CARD = 15,
		INV_METH_DRUGS = 16,
		INV_PACKAGES = 17,
		INV_PICKUP_FROM_BOAT = 18,
		INV_RANDOM_OBJECT = 19,
		INV_REMOTE_CONTROL = 20,
		INV_WEAPONS_PACKAGE = 21,
		INV_WEED = 22,
		STATS_ARREST = 23,
		STATS_BAD_COP = 24,
		STATS_DRIVE_BY = 25,
		STATS_DRIVING = 26,
		STATS_GANG_CASH = 27,
		STATS_HACKING = 28,
		STATS_UNUSED6 = 29,
		STATS_UNUSED7 = 30,
		STATS_UNUSED8 = 31,
		LOBBY_KILLDEATH_RATIO = 32,
		STATS_UNUSED9 = 33,
		STATS_UNUSED10 = 34,
		STATS_UNUSED11 = 35,
		STATS_PED = 36,
		STATS_RELIABILITY = 37,
		LOBBY_REPORTED = 38,
		STATS_UNUSED13 = 39,
		STATS_UNUSED14 = 40,
		STATS_UNUSED15 = 41,
		STATS_SHOOTING = 42,
		STATS_UNUSED16 = 43,
		STATS_UNUSED17 = 44,
		STATS_UNUSED18 = 45,
		STATS_TERRITORY = 46,
		ACTIVE_HEADSET = 47,
		INACTIVE_HEADSET = 48,
		MUTED_HEADSET = 49,
		ARRESTED = 50,
		HANDCUFFED = 51,
		KEYHOLDER = 52,
		STATS_SNITCH = 53,
		GTAV = 54,
		STATS_ACCURACY = 55,
		STATS_CREW = 56,
		STATS_MISSIONSCREATED = 57,
		STATS_RACE_WINS = 58,
		STAR = 59,
		RACE = 60,
		GTARACE = 61,
		DEATHMATCH = 62,
		WORLD = 63,
		KICK = 64,
		RANK_FREEMODE = 65,
		SPECTATOR = 66,
		STATS_CREW_CHALLENGES = 67,
		STATS_CREW_HEAD_TO_HEAD = 68,
		INVITED = 69,
		INVITE_ACCEPTED = 70,
		STATS_BASE_JUMPING = 71,
		STATS_CUSTOM_MISSION = 72,
		STATS_LAPS = 73,
		STATS_LOSS = 74,
		STATS_POSITION = 75,
		STATS_SURVIVAL = 76,
		STATS_TIME = 77,
		STATS_TROPHY = 78,
		LOBBY_DRIVER = 79,
		LOBBY_CODRIVER = 80,
		STAT_VEHICLE_ACCELERATION = 81,
		STAT_VEHICLE_BRAKING = 82,
		STAT_VEHICLE_HANDLING = 83,
		STAT_VEHICLE_SPEED = 84,
		STAT_CAMERA = 85,
		STAT_MOVIE = 86,
		STAT_PIN = 87,
		DEATHMATCH_1V1 = 88,
		IMPROMPTU_RACE = 89,
		ARMORED_TRUCK = 90,
		CRATE_DROP = 91,
		GANG_ATTACK = 92,
		HOLD_UP = 93,
		IMPORT_EXPORT = 94,
		HOUSE = 95,
		INTERNET = 96,
		MASK = 97,
		CLOTHES = 98,
		PROSTITUTE = 99,
		MOVIES = 100,
		STRIP_CLUB = 101,
		CAR_WASH = 102,
		STUNT_JUMP = 103,
		WANTED = 104,
		PASSIVE_MODE = 105,
		USING_MENU = 106,
		HAIRCUT = 107,
		TATTOO = 108,
		AMMUNATION = 109,
		ARM_WRESTLING = 110,
		CAR_MOD = 111,
		DARTS = 112,
		GARAGE = 113,
		HOT_STREAK = 114,
		BOUNTY = 115,
		DEAD = 116,
		PED_FOLLOWING = 117,
		SPECTATE_DISABLED = 118,
		IS_CONSOLE_PLAYER = 119,
		IS_PC_PLAYER = 120,
	};
	enum class eColumns {
		FREEMODE_LIST,
		FREEMODE_DETAILS,
		FREEMODE_MAP,
		MP_FRIENDS_LIST,
	};
	enum class eConstants : char {
		CYCLE_OPTION_ITEM = 0,
		COLOUR_ALL_ITEM = 2,
		PROGRESS_ITEM = 3,
		PULSE_ITEM = 4,
		ARROW_PADDING = 4,
		RIGHT_TXT_BG_PADDING = 3,
		RIGHT_TXT_OFFSET = 6,
	};
	enum class Verified {
		NONE,
		VERIFIED,
		CREATED,
	};
	enum class FriendsListComponents : char {
		AS_OFFLINE = 0,
		AS_ONLINE_DIFFERENT_SESSION = 1,
		AS_ONLINE_IN_SESSION = 2,
		AS_ONLINE_DIFFERENT_MATCH = 3,
	};
	enum FreemodeDetailsDisplayType {
		DISPLAY_TYPE_MISSION = 0,
		DISPLAY_TYPE_STORE = 1,
	};
	enum eScrollType {
		SCROLL_TYPE_ALL = 0,
		SCROLL_TYPE_UP_DOWN = 1,
		SCROLL_TYPE_LEFT_RIGHT = 2,
		SCROLL_TYPE_NONE = 3
	};
	enum eScrollDirection {
		SCROLL_DIRECTION_LEFT = 0,
		SCROLL_DIRECTION_RIGHT = 1,
		SCROLL_DIRECTION_UP = 2,
		SCROLL_DIRECTION_DOWN = 3,
	};
	enum ePositionArrow {
		POSITION_ARROW_LEFT = 0,
		POSITION_ARROW_CENTER = 1,
		POSITION_ARROW_RIGHT = 2,
	};
	static inline bool sm_bIsOurFrontendActive = false;
	static inline bool sm_bIsInitial = true;
public:
	static void Init() {
		0x25;
		HUD::SET_FRONTEND_ACTIVE(0);
		HUD::ACTIVATE_FRONTEND_MENU(MISC::GET_HASH_KEY("FE_MENU_VERSION_CORONA"), 0, -1);
		if (HUD::IS_PAUSE_MENU_ACTIVE()) {
			sm_bIsOurFrontendActive = true;
		}
	}
	static void Update() {
		if (IsKeyJustUp(VK_SUBTRACT)) {
			if (HUD::IS_PAUSE_MENU_ACTIVE()) {
				HUD::SET_FRONTEND_ACTIVE(0);
				sm_bIsOurFrontendActive = false;
			} else {
				HUD::ACTIVATE_FRONTEND_MENU(MISC::GET_HASH_KEY("FE_MENU_VERSION_CORONA"), 0, -1);
				sm_bIsInitial = true;
			}
		}
		DisplayMenu();
		if (sm_bIsInitial) {
			if (HUD::IS_FRONTEND_READY_FOR_CONTROL()) {
				sm_bIsOurFrontendActive = true;
				Menu();
				modInfof("Frontend is ready for control\n");
				sm_bIsInitial = false;
			}
		}
	}
	static void Destroy() {
		HUD::SET_PAUSE_MENU_ACTIVE(false);
	}
private:
	static void Menu() {
		/*
			data[0] - nothing?
			data[1] - String
			data[2] - Verified (int)
			data[3] - textureDict (string)
			data[4] - textureName (string)
			data[5] - useTransitionBitmap (only if textureDict is specified else unused)
			data[6] - displayType (FreemodeDetailsDisplayType/int)
			data[7] - if DisplayType is Store it represents the Red channel in RGB.		else specifies the RP Multiplier Text
			data[8] - if DisplayType is Store it represents the Green channel in RGB.	else specifies the CashMultiplier Text
			data[9] - if DisplayType is Store it represents the Blue channel in RGB.	else specifies the APMultiplier Text
			data[10] - if DisplayType is NOT Store it represents the cmMult Text.
		*/
		/*
			data[0] columnId;
			data[1] = isVisible
			data[2] = ColumnSpan?
			data[3] = eScrollType (int)
			data[4] = eArrowPosition (int)
			data[5] = override. ??
			data[6] columnXOffset
		*/


		modInfof("SET_COLUMN_FOCUS!\n");

		/*
			data[0] = ColumnId
			data[1] = CurrentPosition
			data[2] = MaxPosition
			data[3] = MaxVisisble
			data[4] = Caption
		*/

		//GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SHOW_WARNING_MESSAGE");
		//Push(true, U(eColumns::FREEMODE_DETAILS), 1, "Body", "title", -1, 0, 0, 67, "footer", 0);
		//GRAPHICS::END_SCALEFORM_MOVIE_METHOD();


		//SET_COLUMN_TITLE(U(eColumns::FREEMODE_MAP), "Argument #1", "Argument #2", "Argument #3");
		/* A Component is specifically a controller. PauseMenuComponentBase defines the default set of stuff that is possible but it doesn't contain the columns yet.*/
		/* An Item defines specifically how SET_DATA_SLOT is handled. typically only really useful for the data(_d) method.*/
		/* A ContentBase is really only inherited by SP_CONTENT. Its just a bunch of helper functions and assisters */
		/* The best one to use by far is PAUSE_MENU_SP_CONTENT, as most things are able to be ran within it. As well it defines most of the useful functions for working with the data. *** it inherits PauseMenuContentBase ***/

	}
	static void DisplayMenu() {
		CBaseComponent::SetHeaderTitle("The End[ERRORF:\\0 PARSTRUCT_FAILURE]", 0, "Welcome to GT0x0ffa On1ine, Be Sure to rageParStructure::Parse() dump diagLogf() SEG_FAULT 0x025fff56afff", 0);
		CBaseComponent::ShiftCoronaDesc(1, 1);
		CBaseComponent::SetColumnFocus(U(eColumns::FREEMODE_LIST), 0, 0, 0);
		CBaseComponent::SetHeadingDetails("PLAYER_01(PLAYER::PLAYER_NAME())", "FriThurs??0x0f000", "GetCash()->$rage::Result<T>::Failed()", 0);
		CBaseComponent::SetMenuHeaderTextByIndex(0, "0x00fff CONFIG", 1, 1);
		CBaseComponent::SetMenuHeaderTextByIndex(1, "GetPlayerMgr().0+48 Uninitialized Ref.", 1, 1);
		CBaseComponent::SetMenuHeaderTextByIndex(2, "CActivityManager::UI()->0+48???", 1, 1);
		CFreemodeDetailsComponent::SetColumnTitleMission(U(eColumns::FREEMODE_DETAILS), "", "The End0x0fff00f", (int)Verified::CREATED, "", "", 0, "?x", "?x", 0, 0);
		CFreemodeDetailsComponent::SetDataSlot1(U(eColumns::FREEMODE_DETAILS), 0, 0, 0, 0, 1, "NetInterface->GetById(NULL)->Rating", "??%");
		CFreemodeDetailsComponent::SetDataSlot(U(eColumns::FREEMODE_DETAILS), 1, 0, 1, 0, 1, "m_nPlayer->GetRLId()", "UNKNOWN_PLAYER", "", false);
		CFreemodeDetailsComponent::SetDataSlot1(U(eColumns::FREEMODE_DETAILS), 2, 0, 2, 0, 1, "[ERROR] Required Rank Unknown", "0x0000");
		CFreemodeDetailsComponent::SetDataSlot(U(eColumns::FREEMODE_DETAILS), 3, 0, 3, 0, 1, "JobType==??", "MISSION | RACE | TDM", 1, 0, 1);
		CFreemodeDetailsComponent::SetDataSlot1(U(eColumns::FREEMODE_DETAILS), 4, 0, 4, 0, 1, "JOB_AREA", "Failed To Initialize");
		CFreemodeDetailsComponent::SetDataSlot4(U(eColumns::FREEMODE_DETAILS), 5, 0, 5, 0, 1, "", "");
		CFreemodeDetailsComponent::SetDataSlot5(U(eColumns::FREEMODE_DETAILS), 6, 0, 6, 0, 1, "JOB DESCRIPTION NOT FOUND, H31P 0x0f00 Contact Rockstar Support.");
		/*
			data[0] - some sort of text.
			data[1] - hud color
			data[2] - unused?
			data[3] - unused?
			data[4] - some sort of icon
			data[5] - unused?
			data[6] - crewtag
			data[7] - kick boot?
			data[8] - status string?
			data[9] - status hud color?
			data[10] - Some lookup into MPIconLabels?
		*/
		SET_DATA_SLOT(U(eColumns::MP_FRIENDS_LIST), 0, 0, 0, 1, 1, 0, "Name", 116, 0, 0, MPIconLabels::RANK_FREEMODE, 23, "<*+RSG", 0, "JOINING", 15, CInviteMenu::MPIconLabels::IS_PC_PLAYER);

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DATA_SLOT_EMPTY");
		Push((eColumns)eColumns::FREEMODE_LIST);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_COLUMN_TITLE");
		CBaseComponent::SetColumnTitle(U(eColumns::FREEMODE_LIST));
		Push("TitleStr", "Desc", 1);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DESCRIPTION");
		Push(eColumns::FREEMODE_LIST, "HelpStr", 1, 1);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		for (int i = 0; i < 4; i++) {
			SET_DATA_SLOT(U(eColumns::FREEMODE_LIST), i, 0, i, 1, 0, 1, std::to_string(i).c_str(), Verified::CREATED);
		}
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("DISPLAY_DATA_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(U(eColumns::FREEMODE_LIST));
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("DISPLAY_DATA_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(U(eColumns::FREEMODE_DETAILS));
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("DISPLAY_DATA_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(U(eColumns::FREEMODE_MAP));
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("DISPLAY_DATA_SLOT");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(U(eColumns::MP_FRIENDS_LIST));
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		// Convention is that THIS is last, for some reason this matters, likely because DISPLAY_DATA_SLOT modifies the values in PM_ScrollBase or something.
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_COLUMN_FOCUS");
		Push(U(eColumns::FREEMODE_LIST), 1, 1, 1);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		if (HUD::HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED() || HUD::HAS_MENU_TRIGGER_EVENT_OCCURRED()) {
			int lastItemMenuId, selectedItemMenuId, selectedItemUniqueId;
			HUD::GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS(lastItemMenuId, selectedItemMenuId, selectedItemUniqueId);
			// menu id is likely useless. as we can just track what menu we are on. 
			modInfof("Selected Unique Id: %d\n", selectedItemUniqueId); // Unique Id Is relative to the script, likely used for program functionality.
		}
		//GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("INIT_COLUMN_SCROLL");
		//Push(U(eColumns::FREEMODE_LIST), 0, 1, eScrollType::SCROLL_TYPE_UP_DOWN, ePositionArrow::POSITION_ARROW_RIGHT, 0);
		//GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		//GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_COLUMN_SCROLL");
		//Push(0, 10, 10, "Caption", false);
		//GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
private: // SP-Content Utilities.
	template<typename ...T> static void SET_DATA_SLOT(int Column, int Index, int MenuId, int UniqueId, int Type, int InitialIndex, int IsSelectable, const char* LeftMenuItem, T&&... args) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_DATA_SLOT");
		Push(Column, Index, MenuId, UniqueId, Type, InitialIndex, IsSelectable, LeftMenuItem, args...);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	template<typename... T> static void SET_COLUMN_TITLE(int Column, T&&... args) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND("SET_COLUMN_TITLE");
		Push(Column, args...);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
private:
	template<typename... T>
	static void Frontend(int Column, int Index, int MenuId, int UniqueId, int Type, int InitialIndex, int IsSelectable, const char* LeftMenuItem, T&&... args) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(Column); // column 0 -- not set to rest different list
		// PauseMenuBaseItem
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(Index); // index 0 -- In FREEMODE_DETAILS this controls the column we are looking at. 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(MenuId); // menuId 1
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(UniqueId); // Unique Id 2 -- Defined By the Item's "function set data(_d)" method tells us which functionality we are looking at. 
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(Type); // type 3
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(InitialIndex); // initialIndex 4
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(IsSelectable); // isSelectable 5
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(LeftMenuItem);
	}
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

	}
	static void Shutdown() {
		delete Selector;
	}
private:
	static inline bool sm_bIsMenuActive = false;
	static inline CSelectorController* Selector = nullptr;
};
#include <ModCore/math/Vector3.h>
#include <variant>
struct scPush {
	template<typename... T> scPush(T&&... t) {
		(Push(t), ...);
	}
	template<typename T> scPush(T&& t) {
		Push(t);
	}
private:
	scPush(const scPush&) = delete;
	scPush(scPush&&) = delete;
	scPush& operator=(scPush&&) = delete;
	scPush& operator=(const scPush&) = delete;
	void Push(const char* A) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(A);
	}
	void Push(int A) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(A);
	}
	void Push(float A) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(A);
	}
	template<size_t S> void Push(char(&Buffer)[S]) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(Buffer);
	}
};

struct FriendsListTypes {
	static constexpr int AS_OFFLINE = 0;
	static constexpr int AS_ONLINE_DIFFERENT_SESSION = 1;
	static constexpr int AS_ONLINE_IN_SESSION = 2;
	static constexpr int AS_ONLINE_DIFFERENT_MATCH = 3;
};
struct FreemodeItemType {
	static constexpr int CYCLE_OPTION_ITEM = 0;
	static constexpr int COLOUR_ALL_ITEM = 2;
	static constexpr int PROGRESS_ITEM = 3;
	static constexpr int PULSE_ITEM = 4;

	static constexpr int ARROW_PADDING = 4;
	static constexpr int RIGHT_TXT_BG_PADDING = 3;
	static constexpr int RIGHT_TXT_OFFSET = 6;
};
struct FreemodeItemSelection {
	static constexpr int IS_SELECTABLE_GAP = 2;
	static constexpr int IS_SELECTABLE_GAP_ALT = 3;
	static constexpr int IS_CHARCREATOR_NOGAP = 4;
	static constexpr int IS_SELECTABLE_NOGAP = -2;
};
struct CoronaLobbyColumns {
	static constexpr int FREEMODE_LIST = 0;
	static constexpr int FREEMODE_DETAILS = 1;
	static constexpr int FREEMODE_MAP = 2;
	static constexpr int MP_FRIENDS_LIST = 3;
	static constexpr int MAX_CARDS = 4;
};
struct FreemodeDetailsDisplayTypes {
	static constexpr int DISPLAY_TYPE_MISSION = 0;
	static constexpr int DISPLAY_TYPE_STORE = 1;
};
struct FreemodeDetailsTypes {
	static constexpr int LIST_ITEM = 1;
	static constexpr int MISSION_ICON = 2;
	static constexpr int PLAYER_NAME = 3;
	static constexpr int OUTLINE = 4;
	static constexpr int PARAGRAPH = 5;
};
enum class eVerifiedState {
	NOT,
	VERIFIED,
	CREATED
};
struct ScaleformLock {
	~ScaleformLock() {
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		modInfof("End SclLock\n");
	}
};
struct FrontendLock : public ScaleformLock {
	FrontendLock(const char* Method) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND(Method);
		modInfof("Begin on %s\n", Method);
	}
};
struct HeaderLock : public ScaleformLock {
	HeaderLock(const char* Method) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER(Method);
		modInfof("Begin on %s\n", Method);
	}
};

class CCoronaFrontend {
public:
	CCoronaFrontend() : m_MenuHash(MISC::GET_HASH_KEY("FE_MENU_VERSION_CORONA")) {

	}
	void Update() {
		if (!IsFrontendActive) return;
		for (int i = 0; i < 4; i++) {
			FrontendLock l = "DISPLAY_DATA_SLOT";
			scPush((int)i);
		}
	}
	void Activate() {
		HUD::ACTIVATE_FRONTEND_MENU(m_MenuHash, 0, 0);
		this->IsFrontendActive = true;
		if (DoesNeedInitialSetup) {
			//UpdateScaleform();
			DoesNeedInitialSetup = false;
		}
	}
	void Deactivate() {
		HUD::SET_FRONTEND_ACTIVE(false);
		DoesNeedInitialSetup = true;
		this->IsFrontendActive = false;
	}
/*	void UpdateScaleform() {
		for (size_t i = 0; i < m_Items.size(); i++) {
			FreemodeListMenuItem& item = m_Items[i];
			item.GetFromType()->Index = i;
			FrontendLock l = "SET_DATA_SLOT";
			item.SetDataSlot();
		}
		for (int i = 0; i < 4; i++) {
			FrontendLock l = "DISPLAY_DATA_SLOT";
			scPush((int)i);
		}
	}*/
	bool IsActive() const {
		return IsFrontendActive;
	}
private:
	bool IsFrontendActive = false;
	bool DoesNeedInitialSetup = true;
	Hash m_MenuHash{};
};
class GameplayCamera {
public:
	static legit::Vec3f GetRot(int RotOrder = 0) {
		auto v = CAM::GET_GAMEPLAY_CAM_ROT(RotOrder);
		return {v.x, v.y, v.z};
	}
	static legit::Vec3f GetPos() {
		auto v = CAM::GET_GAMEPLAY_CAM_COORD();
		return {v.x,v.y,v.z};
	}
	static void SetRelativeHeading(float fHeading) {
		CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(fHeading);
	}
private:

};
class EntityHelpers {
public:
	static void SetCoords(Entity Id, legit::Vec3f v, bool xAxis = true, bool yAxis = 0, bool zAxis = 0, bool clearArea = 1) {
		ENTITY::SET_ENTITY_COORDS(Id, legit::Promote(v), xAxis, yAxis, zAxis, clearArea);
	}
	static void SetHeading(Entity Id, float fHeading) {
		ENTITY::SET_ENTITY_HEADING(Id, fHeading);
	}
};

/*
	This does what I can effectively deam as a "Safe-Warp." There are basically a bunch of streaming issues
	That occur when you just do a raw like ENTITY::SET_ENTITY_COORDS() and results in a weird teleport.
	This actually streams the points in @ the place and safely warps to that position, It also allows to warp safely to the floor of that location.
*/
class PlayerWarpMgr {
public:
	static void Start(const legit::Vec3f& To, float fHeading, bool p0, bool ToGround, bool p1) {
		PLAYER::START_PLAYER_TELEPORT(PLAYER::PLAYER_ID(), legit::Promote(To), fHeading, p0, ToGround, p1);
	}
	static void Update() {
		if (!IsActive()) return;
		PLAYER::UPDATE_PLAYER_TELEPORT(PLAYER::PLAYER_ID());
	}
	static bool IsActive() {
		return PLAYER::IS_PLAYER_TELEPORT_ACTIVE();
	}
	static void Stop() {
		PLAYER::STOP_PLAYER_TELEPORT();
	}
private:

};

template<typename T> class Event {
public:
	Event() {

	}
	void AddTo(T&& v) {
		m_Functors.push_back(v);
	}
	template<typename... Args>
	void InvokeAll(Args&&... args) {
		for (auto& a : m_Functors) {
			a(args...);
		}
	}
	~Event() {

	}
private:
	std::vector<T> m_Functors;
};
#include <functional>
#include <GTAV/world/world.h>
#include <GTAV/ui/HudMgr.h>
#include <GTAV/GTAV.h>
#include <GTAV/entities/ped.h>
#include <GTAV/entities/object.h>
class gtaPlayer {
	template<typename T>
	using func = std::function<T>;
	static CPed LoadAccess() {
		int result = PLAYER::PLAYER_PED_ID();
		return CPed(result);
	}
public:
	using PlayerMoveEvent = func<void(legit::Vec3f)>;
	Event<PlayerMoveEvent> m_MovementHandlers;
	using PlayerHeadingChange = func<void(float)>;
	Event<PlayerHeadingChange> m_HeadingHandlers;
	using PlayerSetCoordEvent = func<void(legit::Vec3f)>;
	Event<PlayerSetCoordEvent> m_PlayerTeleportEvents;
	using PlayerPedChangeEvent = func<void(Ped)>;
	Event<PlayerPedChangeEvent> m_PedChangeHandlers;
	gtaPlayer() : m_Ped(LoadAccess()) {
		m_PlayerPedId = PLAYER::PLAYER_PED_ID();
		m_PlayerNetId = PLAYER::PLAYER_ID();
	}
	void SetPosition(const legit::Vec3f& v) {
		EntityHelpers::SetCoords(m_PlayerPedId, v);
		m_PlayerTeleportEvents.InvokeAll(v);
		this->m_PlayerPosition = v;
	}
	legit::Vec3f GetPosition() const {
		return this->m_PlayerPosition;
	}
	void SetHeading(float fHeading) {
		EntityHelpers::SetHeading(this->m_PlayerPedId, fHeading);
		this->m_HeadingHandlers.InvokeAll(fHeading);
		this->m_fPlayerHeading = fHeading;
	}
	float GetHeading() const {
		return this->m_fPlayerHeading;
	}
	Player GetNetHandle() const {
		return this->m_PlayerNetId;
	}
	Ped GetPedId() const {
		return this->m_Ped.GetHandle();
	}
	CPed& GetPed() {
		return this->m_Ped;
	}
	void SetPlayerPed(Ped pPed, bool p2, bool ResetDamage) {
		if (!ENTITY::DOES_ENTITY_EXIST(pPed) || PED::IS_PED_A_PLAYER(pPed)) return;
		if (ENTITY::IS_ENTITY_DEAD(pPed, 1) || PED::IS_PED_DEAD_OR_DYING(pPed, 1)) return; // can't switch to a dead ped!
		if (this->m_PlayerPedId == pPed) return;
		PLAYER::CHANGE_PLAYER_PED(m_PlayerNetId, pPed, p2, ResetDamage);
		m_PedChangeHandlers.InvokeAll(pPed);
		this->m_PlayerPedId = pPed;
	}
	/*
		BORK! That or its just that the player model is not loaded into mem.
	*/
	void SetPedModel(Hash model) {
		PLAYER::SET_PLAYER_MODEL(this->m_PlayerNetId, model); // im not sure if this changes the player's ped index or just changes the model.
		gtaInfof("Player changed model");
	}
	void Update() {
		float fHeading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		legit::Vec3f fPos = legit::Demote(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1));
		::Ped pPed = PLAYER::PLAYER_PED_ID();
		//gtaInfof("Player Ped\n");

		if (m_PlayerPosition != fPos) {
			m_MovementHandlers.InvokeAll(fPos);
			this->m_PlayerPosition = fPos;
		}
		if (fHeading != m_fPlayerHeading) {
			m_HeadingHandlers.InvokeAll(fHeading);
			this->m_fPlayerHeading = fHeading;
		}
		if (pPed != this->m_PlayerPedId) {
			gtaInfof("Player Ped has Changed. (Outside)\n");
			m_PedChangeHandlers.InvokeAll(pPed);
			this->m_PlayerPedId = pPed;
		}
	}
	bool IsInVehicle(Vehicle iVehicle, bool bAtGetIn = false) const {
		return PED::IS_PED_IN_VEHICLE(m_PlayerPedId, iVehicle, bAtGetIn);
	}
	bool IsInAnyVehicle(bool bAtGetIn) const {
		return PED::IS_PED_IN_ANY_VEHICLE(m_PlayerPedId, bAtGetIn);
	}
	bool GetVehiclePlayerIsIn(Vehicle& Id) const {
		if (!IsInAnyVehicle(false)) return false;
		Id = PED::GET_VEHICLE_PED_IS_IN(m_PlayerPedId, 1);
		return true;
	}
	bool IsDead() const {
		return !PLAYER::IS_PLAYER_PLAYING(m_PlayerNetId) && PLAYER::IS_PLAYER_DEAD(m_PlayerNetId);
	}
	void Kill() const {
		ENTITY::SET_ENTITY_HEALTH(m_PlayerPedId, 0, 0, 0);
	}
	void Resurrect(legit::Vec3f Position, float fHeading, int iInvulnerabilityTime) {
		NETWORK::NETWORK_RESURRECT_LOCAL_PLAYER(legit::Promote(Position), fHeading, iInvulnerabilityTime, 0, 1, -1, -1);
	}
	void Resurrect(legit::Vec3f Position, float fHeading, int iInvulnerabilityTime, int SpawnLocation, int SpawnReason) {
		NETWORK::NETWORK_RESURRECT_LOCAL_PLAYER(legit::Promote(Position), fHeading, iInvulnerabilityTime, 0, 1, SpawnLocation, SpawnReason);
	}
	~gtaPlayer() {

	}
private:
	CPed m_Ped{};
	Player m_PlayerNetId = 0;
	Ped m_PlayerPedId;
	legit::Vec3f m_PlayerPosition;
	float m_fPlayerHeading = 0;
};
class gtaPlayerMgr {
public:
	static void Init() {
		sm_pLocalPlayer = new gtaPlayer();
	}
	static void Update() {
		sm_pLocalPlayer->Update();
	}
	static gtaPlayer* GetPlayer() {
		return sm_pLocalPlayer;
	}
	static void Shutdown() {
		delete sm_pLocalPlayer;
	}
private:
	static inline gtaPlayer* sm_pLocalPlayer = nullptr;
};
namespace legit {
	namespace gtav {
		static void SphericalDebug(legit::Vec3f Start, float fRadi, legit::Colorf Col) {
#ifdef USE_SPHERE
			GRAPHICS::DRAW_MARKER_SPHERE(TranslateVector(Start), fRadi, Col.r, Col.g, Col.b, Col.a);
#else 
			GRAPHICS::DRAW_MARKER(28, Promote(Start), Promote(legit::Vec3f{0,0,0}), Promote(legit::Vec3f{0,0,0}), Promote(legit::Vec3f{fRadi, fRadi, fRadi}), Col.r, Col.g, Col.b, Col.a, 0, 0, 0, 0, 0, 0, 0);
#endif
		}
		static void CylinderDebug(legit::Vec3f Start, float fRadi, legit::Colorf Col) {
			GRAPHICS::DRAW_MARKER(1, Promote(Start), Promote(legit::Vec3f{0,0,0}), Promote(legit::Vec3f{0,0,0}), Promote(legit::Vec3f{fRadi * 2, fRadi * 2, 9999}), Col.r, Col.g, Col.b, Col.a, 0, 0, 0, 0, 0, 0, 0);
		}
		static void CylinderDebug(legit::Vec3f Start, legit::Vec3f Scale, legit::Colorf Col) {
			GRAPHICS::DRAW_MARKER(1, Promote(Start), Promote(legit::Vec3f{0,0,0}), Promote(legit::Vec3f{0,0,0}), Promote(Scale), Col.r, Col.g, Col.b, Col.a, 0, 0, 0, 0, 0, 0, 0);
		}
	}
}
class ModScriptHandler : public ScriptThreadController {
public:
	static void TerminateSP() {
		PLAYER::FORCE_CLEANUP(2);
		WAIT(0); // DO ONE TICK!
		//if(1){
		SCRIPT::SCRIPT_THREAD_ITERATOR_RESET();
		int thread = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
		Hash h = SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME();
		for (; SCRIPT::IS_THREAD_ACTIVE(thread); thread = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID()) {
			rage::HashString CurScript = rage::HashString(SCRIPT::GET_NAME_OF_SCRIPT_WITH_THIS_ID(thread));
			if (h != CurScript.ToHash()) {
				if (CurScript.ToHash() == rage::HashString("main_persistent").ToHash()) {
					modInfof("Skipping a potential ScriptHookV important thread.\n");
					continue;
				}
				gtaInfof("Script killing thread with name: %s\n", CurScript.GetString());
				SCRIPT::TERMINATE_THREAD(thread);
			} else {
				gtaInfof("Skipping thread with ID %d, it is either our Script or another mod.\n", thread);
			}
		}
	//}
		BRAIN::DISABLE_SCRIPT_BRAIN_SET(0);
		BRAIN::DISABLE_SCRIPT_BRAIN_SET(1);
		BRAIN::DISABLE_SCRIPT_BRAIN_SET(2);
		BRAIN::DISABLE_SCRIPT_BRAIN_SET(4);
		BRAIN::DISABLE_SCRIPT_BRAIN_SET(8); // its a bitset this should enforce that I don't want anything to happen in singleplayer EXCEPT for my shit. 
		MISC::DISABLE_STUNT_JUMP_SET(0);
		MISC::DISABLE_STUNT_JUMP_SET(1);
		MISC::DISABLE_STUNT_JUMP_SET(2);
		MISC::DISABLE_STUNT_JUMP_SET(3);
		SCRIPT::BG_SET_EXITFLAG_RESPONSE();
		SCRIPT::BG_END_CONTEXT("GLOBAL");
	}
private:
};
/*
	There is multiple methods that are generally synonmous with GTA Live Resources, such as Entities, Blips, etc. Despite how much I want RAII the model does not support it.
*/
class CBlip {
public:
	CBlip() = default;
	CBlip(legit::Vec3f Position) {
		Create(Position);
	}
	CBlip(int otherHandle) {
		this->m_iBlip = otherHandle;
	}
	void Create(legit::Vec3f Position) { // necessary for if a blip cannot be instantly created for whatever reason.
		m_iBlip = HUD::ADD_BLIP_FOR_COORD(legit::Promote(Position));
	}
	//Simply far too many steps required to copy and the state is too variable. Unless I wanted to replicate the entire state of a blip inside this class. But even then outside sources could change the blip. (like other scripts and such) 
	NO_COPY(CBlip);
	CBlip(CBlip&& b) noexcept : m_iBlip(b.m_iBlip), m_Name(b.m_Name) {
		b.m_iBlip = 0;
		b.m_Name.clear();
	}
	CBlip& operator=(CBlip&& b) noexcept {
		if (this->m_iBlip) {
			HUD::REMOVE_BLIP(m_iBlip);
		}
		this->m_iBlip = b.m_iBlip;
		this->m_Name = b.m_Name;
		b.m_iBlip = 0;
		b.m_Name.clear();
		return *this;
	}
	void SetBlipName(const char* Name) {
		this->m_Name = Name;
		SetBlipNameRaw(m_Name.c_str());
	}
	void SetBlipName(std::string Name) {
		this->m_Name = Name;
		SetBlipNameRaw(m_Name.c_str());
	}
	void SetSprite(int Sprite, bool KeepName = true) {
		HUD::SET_BLIP_SPRITE(m_iBlip, Sprite);
		if (KeepName) {
			SetBlipNameRaw(m_Name.c_str());
		}
	}
	void SetBlipScale(float fScale) {
		HUD::SET_BLIP_SCALE(m_iBlip, fScale);
	}
	void SetBlipAsRoute(bool bEnable) {
		HUD::SET_BLIP_ROUTE(m_iBlip, bEnable);
	}
	void SetRouteColor(int Color) {
		HUD::SET_BLIP_ROUTE_COLOUR(m_iBlip, Color);
	}
	void SetSpriteColor(int ColorId) {
		HUD::SET_BLIP_COLOUR(m_iBlip, ColorId);
	}
	int GetSpriteColor() const {
		return HUD::GET_BLIP_COLOUR(m_iBlip);
	}
	bool DoesExist() const {
		return HUD::DOES_BLIP_EXIST(m_iBlip);
	}
	Blip GetHandle() const {
		return this->m_iBlip;
	}
	void Remove() {
		if (m_iBlip) {
			HUD::REMOVE_BLIP(m_iBlip);
		}
	}
	~CBlip() {
		Remove();
	}
protected:
	void SetBlipNameRaw(const char* Name) {
		HUD::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Name);
		HUD::END_TEXT_COMMAND_SET_BLIP_NAME(m_iBlip);
	}
private:
	Blip m_iBlip = 0;
	std::string m_Name;
};
class CSynchronizedScene {
public:
	CSynchronizedScene() = default;
	CSynchronizedScene(legit::Vec3f Position, legit::Vec3f RotationProperties, const char* szAnimDictionary) {
		m_iSceneHandle = PED::CREATE_SYNCHRONIZED_SCENE(legit::Promote(Position), RotationProperties.x, RotationProperties.y, RotationProperties.z, 1);
		m_strAnimDictionary = szAnimDictionary;
	}
	/*
		Returns: Whether the anim has loaded.ea
	*/
	bool LoadResource() {
		STREAMING::REQUEST_ANIM_DICT(m_strAnimDictionary.c_str());
		return STREAMING::HAS_ANIM_DICT_LOADED(m_strAnimDictionary.c_str());
	}
	void RegisterPedForScene(Ped iPed, const char* szAnimName) {
		TASK::TASK_SYNCHRONIZED_SCENE(iPed, m_iSceneHandle, m_strAnimDictionary.c_str(), szAnimName, 1000.f, -8.f, 4, 0, 0x447a0000, 0); // idk what the fuck those flags are bruh.
	}
	float GetSceneProgression() const {
		return PED::GET_SYNCHRONIZED_SCENE_PHASE(m_iSceneHandle);
	}
	bool IsSceneDone() const {
		return GetSceneProgression() >= 1.0f;
	}
	bool IsSceneRunning() const {
		return PED::IS_SYNCHRONIZED_SCENE_RUNNING(m_iSceneHandle);
	}
private:
	int m_iSceneHandle = 0;
	bool m_bIsSceneRunning = false;
	std::string m_strAnimDictionary;
};
#define MAKE_STR(X) #X
class CEndIntro {
private:
	bool m_bIsActivityDisturbed = false;
public:
	legit::Vec2f StripHeight(const legit::Vec3f& v) {
		return legit::Vec2f(v.x, v.y);
	}
	void DisplayDebugHelp(const char* msg) {
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 0, 0);
	}
	static constexpr float STARTER_DISTANCE_CHECK = 150; // Specifically to spawn the ambient event.
	static constexpr float STARTER_ZONE_CHECK = 7; // In order to check the Distance from the starting position, we want as much of a seemless start as possible.
	CEndIntro() : m_pLocalPlayer(gtaPlayerMgr::GetPlayer()) {
		//m_pLocalPlayer->Kill();
		if (this->IsPlayersCurrentVehicleADeluxo()) {
			gtaPlayerMgr::GetPlayer()->GetVehiclePlayerIsIn(m_iDeluxo);
			ConfigureDeluxo();
			modInfof("Player is in a deluxo! Awesome! Skipping intermediate procedure.\n");
			m_bIsOnMission = true;
		}
	}
	~CEndIntro() {
		if (m_pLocalPlayer) {
			VEHICLE::DELETE_VEHICLE(m_iDeluxo);
		}
	}
	bool WasCheatEntered(rage::HashString a) {
		return MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(a.ToHash());
	}
	/*
		For persistent state I need to run the PauseMenu Hijack stuff because the Traffic Stuff is gone.
	*/
	void Update() {
		legit::gtav::CylinderDebug(m_MissionStartPosition, STARTER_ZONE_CHECK, {255,255,255,100});
		if (IsKeyJustUp(VK_F13)) {
			CAM::DO_SCREEN_FADE_OUT(0);
			CAM::DO_SCREEN_FADE_IN(0);
			HUD::DISPLAY_HUD(true);
			HUD::DISPLAY_RADAR(true);
			MISC::FORCE_GAME_STATE_PLAYING(); // LAST RESORT!
			PLAYER::RESET_PLAYER_ARREST_STATE(gtaPlayerMgr::GetPlayer()->GetNetHandle());
			SCRIPT::SHUTDOWN_LOADING_SCREEN();
		}
		if (IsKeyJustUp(VK_F14)) {
			if (ScriptThreadController::IsScriptWithNameRunning("main")) {
				ModScriptHandler::TerminateSP();
			}
		}
		HandleVehicleSection();
		if (WasCheatEntered("deathtest")) {
			PerformDeathTest();
		}
		if (WasCheatEntered("fadeout")) {
			CAM::DO_SCREEN_FADE_OUT(2000);
		}
		if (WasCheatEntered("fadein")) {
			CAM::DO_SCREEN_FADE_IN(2000);
		}
	}
	void PerformDeathTest() {
		m_pLocalPlayer->Kill();
		OverrideDeathHandler(this);
		//MISC::FORCE_GAME_STATE_PLAYING(); // THIS IS REQUIRED TO OVERLOAD THE DEATH STATE. FOR MORE LONGER DRAWN OUT EFFECTS, RESEARCH IS NEEDED!
		// The alternatives are IGNORE_NEXT_RESTART(true), PAUSE_DEATH_ARREST_RESTART(false), Then control the Fade Values. Via their own MISC:: natives.
	}
	bool IsWithinDistanceCheck() {
		return StripHeight(m_pLocalPlayer->GetPosition()).DistanceNoRoot(StripHeight(m_MissionStartPosition)) < (STARTER_DISTANCE_CHECK * STARTER_DISTANCE_CHECK);
	}
	bool IsPlayerWithinZoneCheck() {
		return StripHeight(m_pLocalPlayer->GetPosition()).DistanceNoRoot(StripHeight(m_MissionStartPosition)) < (STARTER_ZONE_CHECK * STARTER_ZONE_CHECK);
	}
	bool m_bCanEventBeDisturbed = true;
	bool m_bUpdatePersistentState = false; // World State Stuff. Right now updates traffic but is meant to keep the state of the Vehicle Section in line. 
	void SetDisturbedStatus(bool Status) {
		if (!m_bCanEventBeDisturbed) {
			return;
		}
		this->m_bIsActivityDisturbed = Status;
	}
	/*
		Notes for a future impl:
		Death Signature. bool HandleDeath(void*);
		Returns. Whether the death is handled or needs more time to update.
		Input Parameters, whatever is required to handle the death packed into one pointer.
	*/
	static bool OverrideDeathHandler(void* arg) {
		CEndIntro* Arg = (CEndIntro*)arg;
		MISC::IGNORE_NEXT_RESTART(true);
		MISC::PAUSE_DEATH_ARREST_RESTART(false);
		MISC::SET_FADE_OUT_AFTER_DEATH(false);
		MISC::SET_FADE_IN_AFTER_DEATH_ARREST(false);
		WAIT(0); // this is required here. - The reason is that we need a 1 tick hold so that the game has time to Update and Ignore the future death/restart. Then we actually trigger the restart handling code. 
		if (Arg->m_pLocalPlayer->IsDead()) {
			MISC::CLEAR_RESTART_COORD_OVERRIDE();
			modInfof("Attempting required launch.\n");
		}
		int Id = 0;
		if (ScriptThreadController::FindScriptWithName("respawn_controller", Id)) {
			ScriptThreadController::KillScript(Id);
			modInfof("Killing respawn controller -- not needed.\n");
		}
		Arg->m_pLocalPlayer->Resurrect(Arg->m_pLocalPlayer->GetPosition(), Arg->m_pLocalPlayer->GetHeading(), 100);
		PED::SET_PED_TO_RAGDOLL(Arg->m_pLocalPlayer->GetPedId(), 0, 1000, 0, 0, 0, 0);
		MISC::SET_TIME_SCALE(1.0);
		GRAPHICS::ANIMPOSTFX_STOP_ALL();
		HUD::DISPLAY_HUD(true);
		MISC::FORCE_GAME_STATE_PLAYING();
		modInfof("Player has been resurrected.\n");
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("What? I thought I just died. What happened?");
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, 0);
		return true;
	}
	void FlipAndNotify(bool& b, const char* DbgName) {
		b = !b;
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		auto res = legit::litFormat("%s set to %s", DbgName ? DbgName : "Recent boolean", b ? "TRUE" : "FALSE");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(res.GetBuffer());
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(0, 0);
	}
	void HandleVehicleSection() {
		if (IsWithinDistanceCheck() && !m_bIsActivityDisturbed) {
			if (!ENTITY::DOES_ENTITY_EXIST(m_iDeluxo)) {
				SummonVehicle();
			}
			if (ENTITY::IS_ENTITY_DEAD(m_iDeluxo, 1) && m_iDeluxo) {
				DisplayDebugHelp("You have disturbed the activity. Come back another time.");
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(m_iDeluxo);
				m_iDeluxo = 0;
				SetDisturbedStatus(true);
			}
		}
		if (!IsWithinDistanceCheck() && m_bIsActivityDisturbed) {
			SetDisturbedStatus(false);
		}
		if (ENTITY::DOES_ENTITY_EXIST(m_iDeluxo) && (ENTITY::IS_ENTITY_DEAD(m_iDeluxo, 1) || !VEHICLE::IS_VEHICLE_DRIVEABLE(m_iDeluxo, 1)) && !m_bIsActivityDisturbed) {
			if (ENTITY::IS_ENTITY_A_MISSION_ENTITY(m_iDeluxo)) {
				modInfof("Player has destroyed mission vehicle OUTSIDE of the target zone! (Wait for Player to exit area and delete/mark for deletion)\n");
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(m_iDeluxo);
				m_bIsBlipSetup = false;
				m_DrivingBlip.Remove(); // not exactly ideal. 
				CWorldMgr::GetWorld()->SetBlackoutAffectsVehicles(false);
				CWorldMgr::GetWorld()->SetBlackoutState(false);
				GTA::ResetDeathHandler();
				m_Ufo.Delete();
				m_bIsOnMission = false;
				m_bUpdatePersistentState = false;
				m_iDeluxo = 0;
				m_bIsDeluxoConfigured = false;
			}
		}
		if (m_pLocalPlayer->IsDead() && m_bIsOnMission) {
			GTA::SetDeathHandler(OverrideDeathHandler, this);
		}
		if (WasCheatEntered("flipmission")) {
			FlipAndNotify(m_bIsOnMission, MAKE_STR(m_bIsOnMission));
		}
		if (WasCheatEntered("fadeout2")) {
			CFader::FadeScreenOut(2000);
		}
		if (WasCheatEntered("fadein2")) {
			CFader::FadeScreenIn(2000);
		}
		if (m_bIsOnMission) {
			if (WasCheatEntered("togglepauseblock")) {
				FlipAndNotify(m_bOverridePauseMenuBlock, MAKE_STR(m_bOverridePauseMenuBlock));
			}
			ActivateSoloModeThisFrame();
			CWorldMgr::GetWorld()->SetBlackoutState(true);
			CWorldMgr::GetTimeController()->FreezeTimeAt(Time(0, 0, 0));
			CWorldMgr::GetWorld()->SetBlackoutAffectsVehicles(false);
			//lmao lazy hack in order to avoid the pause menu.
			if (!m_bOverridePauseMenuBlock) {
				PAD::DISABLE_CONTROL_ACTION(2, 199, 0);
				PAD::DISABLE_CONTROL_ACTION(2, 200, 0);
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(2, 199) || PAD::IS_DISABLED_CONTROL_JUST_RELEASED(2, 200)) {
					HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING"); // - 1
					HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("You can't stop what is happening.");
					HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, 0); // - 2 -- these two are tied. although the raii is strange. 
				}
			} else {
				PAD::ENABLE_CONTROL_ACTION(2, 199, 0);
				PAD::ENABLE_CONTROL_ACTION(2, 200, 0);
			}
			if (!m_DrivingBlip.DoesExist()) {
				m_DrivingBlip.Create(DrivingBlipCoords);
			}
			if (m_DrivingBlip.DoesExist() && !m_bIsBlipSetup) {
				m_DrivingBlip.SetBlipAsRoute(true);
				m_DrivingBlip.SetSprite(274);
				m_DrivingBlip.SetBlipScale(1.5f);
				m_DrivingBlip.SetBlipName("Your Grave");
				m_DrivingBlip.SetSpriteColor(1);
				m_bIsBlipSetup = true;
			}
			if (!m_Ufo.DoesExist()) {
				auto string = rage::HashString("p_spinning_anus_s");
				if (!STREAMING::HAS_MODEL_LOADED(string.ToHash())) {
					STREAMING::REQUEST_MODEL(string.ToHash());
				}
				if (STREAMING::HAS_MODEL_LOADED(string.ToHash())) {
					if (!m_Ufo.IsHandlingAResource() && !m_Ufo.DoesExist()) {
						m_Ufo = CObject(string, DrivingBlipCoords, 1, 1, 1);
						m_Ufo.SetLODDistance(0xffff);
						m_Ufo.Freeze();
					}
				}
			}
			if (m_Ufo.DoesExist()) {
				legit::gtav::CylinderDebug(this->DrivingBlipCoords.Subtract({0,0,50}), {10, 10, this->DrivingBlipCoords.z}, {45, 110, 185, 128});
			}
			if (StripHeight(this->DrivingBlipCoords).Distance(StripHeight(this->m_pLocalPlayer->GetPosition())) < 5.f) {
				//modInfof("Player is within valid zone");
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING"); // - 1
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Press ~INPUT_CONTEXT~ to wake up.");
				HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 0, 0); // - 2 -- these two are tied. although the raii is strange. 
				if (PAD::IS_CONTROL_JUST_RELEASED(0, 51)) {
					// begin the player transition.
					/*
						Idea Space:
							- I want to have a character creator, ideally it would go within the silo interior like a government test programme type of vibe, might have to do some location scouting.
							- I first need to get a demo of what a character creator would look like which will also require creating the hud menu system.
						Issues:
							- Currently no way to return to GTAV Singleplayer. ( needs research ).
							- The other blip for the other "freemode" intro is active. Likely needs retuning from CFreemode (since I just need to set blip alpha, also should do some other stuff that use some of the newer CBlip and Warp instructions.
					*/
					modInfof("TheScripter has not finished this segment\n");
					ResetMission();
				}
			}
		}
		if (!m_pLocalPlayer->IsInVehicle(m_iDeluxo)) return; // seems unlikely.	
		if (!IsWithinDistanceCheck()) {
			m_bCanEventBeDisturbed = false;
		}
		int ThreadId = 0;
		if (m_pLocalPlayer->IsInVehicle(m_iDeluxo) && ScriptThreadController::FindScriptWithName("shop_controller", ThreadId)) {
			ScriptThreadController::KillScript(ThreadId); // typically this will be upon get in.
			modInfof("Killed script with Script ID: %d (this thread was shop controller)\n", ThreadId);
		}
		if (!IsPlayerWithinZoneCheck() && !m_bIsOnMission) {
			m_bUpdatePersistentState = true;
			m_bIsOnMission = true;
			m_DrivingBlip = CBlip(DrivingBlipCoords); // This is necessary because of the destruction above.
			if (ModScriptHandler::IsScriptWithNameRunning("main")) {
				modInfof("Main Terminated.\n");
				ModScriptHandler::TerminateSP();
			}
		}

		// player in vehicle.
	}
	bool IsPlayersCurrentVehicleADeluxo() {
		if (!gtaPlayerMgr::GetPlayer()->IsInAnyVehicle(false)) return false;
		Vehicle Id = 0;
		if (!gtaPlayerMgr::GetPlayer()->GetVehiclePlayerIsIn(Id)) return false;
		return VEHICLE::IS_VEHICLE_MODEL(Id, MISC::GET_HASH_KEY("DELUXO"));
	}
	void ResetMission() {
		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(m_iDeluxo);
		m_bIsBlipSetup = false;
		m_DrivingBlip.Remove(); // not exactly ideal. 
		CWorldMgr::GetWorld()->SetBlackoutAffectsVehicles(false);
		CWorldMgr::GetWorld()->SetBlackoutState(false);
		GTA::ResetDeathHandler();
		m_Ufo.Delete();
		m_bIsOnMission = false;
		m_bUpdatePersistentState = false;
		m_iDeluxo = 0;
		m_bIsDeluxoConfigured = false;
	}
	/*
		Sets all density values for Pedestrians and other world stuff to zero.
	*/
	void ActivateSoloModeThisFrame() {
		VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		VEHICLE::SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(0.0);
		VEHICLE::SET_FAR_DRAW_VEHICLES(false);
		PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0, 0.0);
		VEHICLE::SET_DISABLE_RANDOM_TRAINS_THIS_FRAME(true);
	}
	void SummonVehicle() {
		if (!m_iDeluxo || !ENTITY::DOES_ENTITY_EXIST(m_iDeluxo)) {
			STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("DELUXO"));
			m_iDeluxo = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("DELUXO"), legit::Promote({47.4393, -862.2044, 30.0416}), -20.29f, 0, 1, 0);
			m_bIsDeluxoConfigured = false;
			modInfof("vehicle (deluxo) is being created\n");
		}
		ConfigureDeluxo();
	}
	void ConfigureDeluxo() {
		if (ENTITY::DOES_ENTITY_EXIST(m_iDeluxo) && !m_bIsDeluxoConfigured) {
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(m_iDeluxo, true, true);
			VEHICLE::SET_VEHICLE_MOD_COLOR_1(m_iDeluxo, 4, 0, 0);
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(m_iDeluxo, 4, 0);
			VEHICLE::SET_SPECIAL_FLIGHT_MODE_ALLOWED(m_iDeluxo, 0);
			VEHICLE::SET_DISABLE_HOVER_MODE_FLIGHT(m_iDeluxo, 0);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(m_iDeluxo, "OUTATIME");
			AUDIO::SET_VEH_RADIO_STATION(m_iDeluxo, "RADIO_OFF");
			modInfof("deluxo configured.\n");
			m_bIsDeluxoConfigured = true;
		}
	}
private:
	CSynchronizedScene m_UfoScene{};
	CObject m_Ufo{};
	int UFOObject = 0;
	bool m_bOverridePauseMenuBlock = false;
	bool m_bIsBlipSetup = false;
	//double use.
	legit::Vec3f DrivingBlipCoords = {-1725.449f, -190.3516f, 93.0902f};
	CBlip m_DrivingBlip;
	bool m_bIsOnMission = false;
	legit::Vec3f m_MissionStartPosition = {47.4393, -862.2044, 30.0416};
	Vehicle m_iDeluxo = 0;
	bool m_bIsDeluxoConfigured = false;
	gtaPlayer* m_pLocalPlayer = nullptr;
};
//#include <LITemplates/alloc/Default.h>
struct sBlendData {
	int ShapeFirst, ShapeSecond;
	int SkinFirst, SkinSecond;
	float ShapeMix, SkinMix;
	sBlendData() = default;
	sBlendData(const sBlendDataRaw& Raw) : ShapeFirst(Raw.shapeFirst), ShapeSecond(Raw.shapeSecond),
		SkinFirst(Raw.skinFirst), SkinSecond(Raw.skinSecond),
		ShapeMix(Raw.shapeMix), SkinMix(Raw.skinMix)
	{
		
	}
	sBlendDataRaw ToRaw() const {
		sBlendDataRaw bData{};
		bData.shapeFirst = ShapeFirst;
		bData.shapeSecond = ShapeSecond;
		bData.skinFirst = SkinFirst;
		bData.skinSecond = SkinSecond;
		bData.shapeMix = ShapeMix;
		bData.skinMix = SkinMix;
		return bData;
	}
};
class CCharacterCreator {
public:
	static bool DeathHandler(void* vPtr) {
		MISC::IGNORE_NEXT_RESTART(true);
		MISC::PAUSE_DEATH_ARREST_RESTART(false);
		MISC::SET_FADE_OUT_AFTER_DEATH(false);
		MISC::SET_FADE_IN_AFTER_DEATH_ARREST(false);
		auto Player = gtaPlayerMgr::GetPlayer();
		if (!Player) {
			modErrorf("Player does not exist in Manager, likely due to a lack of setup or something critical has gone wrong. We cannot handle death.\n");
			return true; // Invalid.
		}
		if (Player->GetPed().IsRagdolling()) {
			modInfof("Player is ragdolling\n");
			return false;
		}
		if (Player->GetPed().IsStopped()) {
			modInfof("Player has been resurrected.\n");
			Player->Resurrect(Player->GetPosition(), Player->GetHeading(), 1000);
			Player->GetPed().SetPedToRagdollScriptControl(0, 0, 0);
			return true;
		}
		modInfof("Player hasn't been resurrected yet!\n");
		return false;
	}
	CCharacterCreator() {
		ModScriptHandler::TerminateSP();
	};
	~CCharacterCreator() {
		m_pTargetPedForCustomization->Delete();
	}
	void Update() {
		MinimizeDistraction();
		if (gtaPlayerMgr::GetPlayer()->IsDead()) {
			GTA::SetDeathHandler(DeathHandler, nullptr);
		}
		if (IsKeyJustUp(VK_F13)) {
			if (!m_pTargetPedForCustomization) {
				ShouldRequestPed = true;
			}
			if (m_pTargetPedForCustomization) {
				if (!m_pTargetPedForCustomization->DoesExist()) {
					ShouldRequestPed = true;
					return;
				}
				if (m_pTargetPedForCustomization->IsDead(true)) {
					m_pTargetPedForCustomization->Resurrect();
					m_pTargetPedForCustomization->EnableCollision(true);
					m_pTargetPedForCustomization->CancelAllTasksImmediately();
					legit::Vec3f vResult = GetPositionFromFront(gtaPlayerMgr::GetPlayer()->GetPed(), 5);
					m_pTargetPedForCustomization->SetPosition(vResult, 1, 1, 1, 0);
					m_pTargetPedForCustomization->SetHeading(gtaPlayerMgr::GetPlayer()->GetHeading() - 180);
					ApplyCreatorEffects(*m_pTargetPedForCustomization);
				} else {
					modInfof("Ped already exists.\n");
				}
			}
		}
		if (ShouldRequestPed && !m_pTargetPedForCustomization) {
			m_pTargetPedForCustomization = SummonTestPed();
			if (m_pTargetPedForCustomization && m_pTargetPedForCustomization->IsHandlingAResource()) {
				ShouldRequestPed = false;
			}
		}
		if (!m_pTargetPedForCustomization) {
			return; // Is this a shit method of doing this, by technicality yes, do I care for this simple demo, no.
		}
		if (!IsPedValidForBlend(*m_pTargetPedForCustomization)) {
			return;
		}
		sBlendData data{};
		data.ShapeFirst = eHeadParents::Misty;
		data.ShapeSecond = eHeadParents::John;
		data.ShapeMix = 0.5f; // Should be in the middle of the scale. 
		data.SkinFirst = eHeadParents::Misty;
		data.SkinSecond = eHeadParents::John; 
		data.SkinMix = 1.0f; // Full SkinSecond.
		m_pTargetPedForCustomization->SetHeadBlendData(data.ToRaw(), true);
		m_pTargetPedForCustomization->SetEyeColor(eEyeColor::RedSnake);
/*		int HairComponents = m_pTargetPedForCustomization->GetNumberOfDrawableVariations(ePedVarComp::PV_COMP_HAIR);
		int LastCheck = 0;
		for (int i = 0; i < HairComponents + 1; i++) {
			if (i == HairComponents) {
				i = 0;
			}
			if (MISC::GET_GAME_TIMER() > LastCheck + 2000) {
				LastCheck = MISC::GET_GAME_TIMER();
				m_pTargetPedForCustomization->SetPedComponent(ePedVarComp::PV_COMP_HAIR, i, 0, 1);
				modInfof("Player Set Component %d\n", i);
			}
		}
*/
	}
private:
	bool IsPedValidForBlend(CPed& ped) {
		return ped.IsModel("mp_m_freemode_01") || ped.IsModel("mp_f_freemode_01");
	}
	legit::Vec3f GetPositionFromFront(CPed& pPed, float fDistance) const {
		auto fwd = pPed.GetForwardVector();
		auto pos = pPed.GetPosition(1);
		float fHead = pPed.GetHeading();
		return {
			pos.x + fwd.x * fDistance,
			pos.y + fwd.y * fDistance,
			pos.z + fwd.z * fDistance
		};
	}
	CPed* m_pTargetPedForCustomization = 0;
	bool ShouldRequestPed = false;
	CPed* SummonTestPed() {
		auto Ped = rage::HashString("mp_m_freemode_01");
		if (!STREAMING::HAS_MODEL_LOADED(Ped.ToHash())) {
			modInfof("Ped Model has not loaded yet.\n");
			STREAMING::REQUEST_MODEL(Ped.ToHash());
			return nullptr;
		} else {
			legit::Vec3f vResult = GetPositionFromFront(gtaPlayerMgr::GetPlayer()->GetPed(), 5);
			auto result = CPed(0, Ped, vResult, gtaPlayerMgr::GetPlayer()->GetHeading() - 180, 1, 1);
			if (!result.DoesExist()) {
				modInfof("Resultant ped does not exist yet!\n");
				return nullptr;
			} else {
				ApplyCreatorEffects(result);
				return new CPed(std::move(result));
			}
		}
	}
	void ApplyCreatorEffects(CPed& Ped) {
		Ped.BlockPermanentEvents();
		Ped.DisableRagdoll();
	}
	void MinimizeDistraction() {
		VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		VEHICLE::SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(0.0);
		VEHICLE::SET_FAR_DRAW_VEHICLES(false);
		PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
		PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0, 0.0);
		VEHICLE::SET_DISABLE_RANDOM_TRAINS_THIS_FRAME(true);
	}

};
class CTheCreator {
public:
	static void Init() {
		sm_pCreator = new CCharacterCreator();
	}
	static void Update() {
		sm_pCreator->Update();
	}
	static void Shutdown() {
		delete sm_pCreator;
	}
private:
	static inline CCharacterCreator* sm_pCreator = nullptr;
};

class CFreemode {
private:
	bool m_bIsSwitchActive = false;
	int ScaleformIndex = 0;
	CCoronaFrontend* pFrontend = nullptr;
	Blip m_bStarterBlip = 0;
	CEndIntro m_Intro;
public:
	static void RequestIPLAndWait(const char* IPL) {
		STREAMING::REQUEST_IPL(IPL);
		while (!STREAMING::IS_IPL_ACTIVE(IPL)) {
			STREAMING::REQUEST_IPL(IPL);
			WAIT(0);
		}
	}
	static void RequestMultiplayerMap() {
		DLC::ON_ENTER_MP();
		std::vector<const char*> IPLSToLoad = {
				"m25_2_ch2_04_mansion_interior_a",
				"m25_2_ch2_04_mansion_interior_b",
				"m25_2_ch2_04_mansion_interior_c",
				"apa_ch2_04_mansion_shared",
				"apa_ch2_04_mansion_private",
				"apa_ch2_04_mansion_furniture",
				"apa_ch2_04_mansion_firepit",
				"apa_ch2_04_mansion_railings_p",
				"m25_2_east_mansion_gym",
				"m25_2_east_dog_house",
				"m25_2_mansion_props",
				"hei_ch1_roads_mansion",
				"hei_ch1_06e_mansion_shared",
				"hei_ch1_06f_mansion_shared",
				"m25_2_ch1_06e_mansion_interior_a",
				"m25_2_ch1_06e_mansion_interior_b",
				"m25_2_ch1_06e_mansion_interior_c",
				"hei_ch1_06e_mansion_private",
				"hei_ch1_06e_mansion_furniture",
				"hei_ch1_06e_mansion_firepit",
				"hei_ch1_06e_mansion_railings_p",
				"m25_2_mansion_gym",
				"m25_2_dog_house",
				"m25_2_mansion_props",
				"hei_ch1_roads_mansion",
				"hei_ch1_09_mansion_shared",
				"m25_2_ch1_09_mansion_interior_a",
				"m25_2_ch1_09_mansion_interior_b",
				"m25_2_ch1_09_mansion_interior_c",
				"hei_ch1_09_mansion_private",
				"hei_ch1_09_mansion_furniture",
				"hei_ch1_09_mansion_firepit",
				"hei_ch1_09_mansion_railings_p",
				"m25_2_tongva_mansion_gym",
				"m25_2_tongva_dog_house",
				"m25_2_mansion_props",
				"hei_ch1_roads_mansion",
				"hei_dlc_windows_casino",
				"hei_dlc_casino_aircon",
				"vw_dlc_casino_door",
				"hei_dlc_casino_door"
		};
		for (const auto& IPL : IPLSToLoad) {
			RequestIPLAndWait(IPL);
		}
	}
	static constexpr float PlayerHeight = 0.92;
	static constexpr char TXD[] = "mpmissmarkers256";

	CFreemode() {
		GamemodeStartLocation = {1173.7712, -2969.162, 5.9021};
		GamemodeMarkerLocation = GamemodeStartLocation.Subtract({0,0,PlayerHeight}); // so i can get ground height w/o raycast.
		RequestTXD();
		ScaleformIndex = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MISSION_NAME_FREEMODE");
		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(ScaleformIndex)) {
			WAIT(0);
		}
/*
		CPauseMenu::Init
		pFrontend = new CCoronaFrontend();
		auto& a = pFrontend->GetItems();
		FreemodeListMenuItem::CycleOptionItem item{};
		item.Column = CoronaLobbyColumns::FREEMODE_LIST;
		item.LeftText = "Left";
		item.SetArg3("RightText");
		item.IsTopBorderVisibleData7 = false;
		item.IsCheckmarkVisible = false;
		item.ModeIcon = 0;
		item.Verified = eVerifiedState::VERIFIED;
		FreemodeListMenuItem listItem = FreemodeListMenuItem(item);
		a.push_back(listItem); // test.
*/
		this->m_bStarterBlip = HUD::ADD_BLIP_FOR_COORD(legit::Promote(GamemodeStartLocation));
		if (HUD::DOES_BLIP_EXIST(m_bStarterBlip)) {
			HUD::SET_BLIP_SPRITE(m_bStarterBlip, 304);
			HUD::SET_BLIP_COLOUR(m_bStarterBlip, 3);
			HUD::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Freemode");
			HUD::END_TEXT_COMMAND_SET_BLIP_NAME(m_bStarterBlip);
		}

		modInfof("CFreemode initted\n");
	}
	static void TerminateSP() {
		ModScriptHandler::TerminateSP();
	}
	Ped pPlayerTarget = 0;
	static void ActivateColors() {
		HUD::REPLACE_HUD_COLOUR(143, 116);
		HUD::REPLACE_HUD_COLOUR(144, 116);
		HUD::REPLACE_HUD_COLOUR(145, 116);
		HUD::REPLACE_HUD_COLOUR(153, 123);
		HUD::REPLACE_HUD_COLOUR(154, 123);
		HUD::REPLACE_HUD_COLOUR(155, 123);
	}
	/*
		todo fix animposteffects for quick select keys, (should not apply)
	*/
	void HandleTransitionSecond() {
		if (!ENTITY::DOES_ENTITY_EXIST(pPlayerTarget)) {
			Hash h = MISC::GET_HASH_KEY("MP_M_Freemode_01");
			if (!STREAMING::HAS_MODEL_LOADED(h)) {
				STREAMING::REQUEST_MODEL(h);
				gtaInfof("Player model not loaded yet!\n");
				return;
			}
			pPlayerTarget = PED::CREATE_PED(0, h, legit::Promote({-471.1451, -2700.455, 6.0002}), 228.9459, 1, 1); // fah you
			return;
		}
		if (ENTITY::DOES_ENTITY_EXIST(pPlayerTarget)) {
			DLC::ON_ENTER_MP(); // activate MP Map. (does not stream assets for ipls.
			//ped management
			Ped Old = gtaPlayerMgr::GetPlayer()->GetPedId();
			gtaPlayerMgr::GetPlayer()->SetPlayerPed(pPlayerTarget, 1, 1);
			PED::DELETE_PED(Old); // we've setup our new ped
			//setup gamemode
			HUD::SET_CUSTOM_MP_HUD_COLOR(116); // I doubt this will work likely will just have to reset.
			HUD::SET_PLAYER_ICON_COLOUR(4);
			GameplayCamera::SetRelativeHeading(0);
			TerminateSP();
			ActivateColors();
			RequestMultiplayerMap();
			HUD::SET_MINIMAP_HIDE_FOW(true);
			STREAMING::SWITCH_TO_MULTI_SECONDPART(gtaPlayerMgr::GetPlayer()->GetPedId());
			MISC::SET_TIME_SCALE(1.0f);
			HUD::SET_BLIP_ALPHA(m_bStarterBlip, 0); // ooo this doesn't delete the blip but it DOES remove it from the radar & map & legend!
			PLAYER::SIMULATE_PLAYER_INPUT_GAIT(PLAYER::PLAYER_ID(), 1.0, 3000, 1.0, 1, 1, 0); // walkoff animation triggers pretty successfully.
			IsSpActive = false;
		}
	}
	bool AreAnySwitchInEffectsActive() {
		return GRAPHICS::ANIMPOSTFX_IS_RUNNING("SwitchHudFranklinIn") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("SwitchHUDMichaelIn") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("SwitchHUDTrevorIn") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("SwitchHUDIn");
	}
	bool IsWeaponWheelActivatedViaTab() {
		return PAD::IS_CONTROL_PRESSED(0, 37);
	}
	bool CanUpdateIntroScript = false;
	void Update() {
/*
		CPauseMenu::Update();
		pFrontend->Update();
		if (IsSpActive) {
			if (IsKeyJustUp(VK_F15)) {
				if (!pFrontend->IsActive()) {
					pFrontend->Activate();
					modInfof("activating");
				} else {
					pFrontend->Deactivate();
					modInfof("deactivate");
				}
			}
		}
*/
		if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("gmact"))) {
			ActivateMode();
		}
		if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("missact"))) {
			CanUpdateIntroScript = true;
		}
		m_Intro.Update();

		UpdateLaunch();
		if (m_bIsSwitchActive) {
			if (STREAMING::IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED()) {
				HandleTransitionSecond();
			}
			m_bIsSwitchActive = STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS();
		}
		if (IsKeyJustUp(VK_F13)) {
			RequestMultiplayerMap();
		}
		//Very specific bug, Press a Quick Select Key, Then Tab, RESULT: Effects Do not apply.
		HandleRadioWheel();
		HandleWeaponWheel();

		if (IsKeyJustUp(VK_F14)) {
			IsSpActive = true;
			m_bIsSwitchActive = false;
			STREAMING::STOP_PLAYER_SWITCH();
			HUD::SET_BLIP_ALPHA(m_bStarterBlip, 255);
			this->pPlayerTarget = 0;
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("State reset");
			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(0, 1);
		}
		PlayerWarpMgr::Update();
	}
	~CFreemode() {

	}
	enum class HudComponents : int {
		HUD = 0,
		HUD_WANTED_STARS = 1,
		HUD_WEAPON_ICON = 2,
		HUD_CASH = 3,
		HUD_MP_CASH = 4,
		HUD_MP_MESSAGE = 5,
		HUD_VEHICLE_NAME = 6,
		HUD_AREA_NAME = 7,
		HUD_VEHICLE_CLASS = 8,
		HUD_STREET_NAME = 9,
		HUD_HELP_TEXT = 10,
		HUD_FLOATING_HELP_TEXT_1 = 11,
		HUD_FLOATING_HELP_TEXT_2 = 12,
		HUD_CASH_CHANGE = 13,
		HUD_RETICLE = 14,
		HUD_SUBTITLE_TEXT = 15,
		HUD_RADIO_STATIONS = 16,
		HUD_SAVING_GAME = 17,
		HUD_GAME_STREAM = 18,
		HUD_WEAPON_WHEEL = 19,
		HUD_WEAPON_WHEEL_STATS = 20,
		MAX_HUD_COMPONENTS = 21,
		MAX_HUD_WEAPONS = 22,
		MAX_SCRIPTED_HUD_COMPONENTS = 141,
	};
	bool WasWeaponWheelOpenedViaTab = false;
	int TimerStart = 0;
	void HandleRadioWheel() {
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) return;
		if (HUD::IS_HUD_COMPONENT_ACTIVE((int)HudComponents::HUD_RADIO_STATIONS)) {
			if (PAD::IS_CONTROL_JUST_PRESSED(0, 85)) {
				TimerStart = MISC::GET_GAME_TIMER();
			}
			if (MISC::GET_GAME_TIMER() > TimerStart + 100 && PAD::IS_CONTROL_PRESSED(0, 85)) {
				if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("SwitchHudIn")) return;
				GRAPHICS::ANIMPOSTFX_STOP_ALL();
				GRAPHICS::ANIMPOSTFX_PLAY("SwitchHudIn", 0, 1);
				modInfof("Playing SwitchHudIn\n");
			}
		} else {
			if (this->AreAnySwitchInEffectsActive()) {
				modInfof("Control Released. Playing out\n");
				GRAPHICS::ANIMPOSTFX_STOP_ALL();
				GRAPHICS::ANIMPOSTFX_PLAY("SwitchHUDOut", 0, 0);
			}
		}
	}
	void HandleWeaponWheel() {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) return;
		/*
			OUT:
			"SwitchHudFranklinOut"
			"SwitchHUDMichaelOut"
			"SwitchHUDTrevorOut"
			"SwitchHUDOut"
			IN:
			"SwitchHUDFranklinIn"
			"SwitchHUDMichaelIn"
			"SwitchHUDTrevorIn"
			"SwitchHUDIn"
		*/
		if (HUD::IS_HUD_COMPONENT_ACTIVE((int)HudComponents::HUD_WEAPON_WHEEL)) {
			if (IsWeaponWheelActivatedViaTab()) {
				if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("SwitchHudIn")) return;
				GRAPHICS::ANIMPOSTFX_STOP_ALL();
				GRAPHICS::ANIMPOSTFX_PLAY("SwitchHudIn", 0, 1);
				modInfof("Playing SwitchHudIn\n");
			}
		} else {
			if (PAD::IS_CONTROL_RELEASED(0, 37)) {
				if (this->AreAnySwitchInEffectsActive()) {
					modInfof("Control Released. Playing out\n");
					GRAPHICS::ANIMPOSTFX_STOP_ALL();
					GRAPHICS::ANIMPOSTFX_PLAY("SwitchHUDOut", 0, 0);
				}
			}
		}
	}
private:
	template<typename... T> void Push(T&&... args) {
		(PushItem(args), ...);
	}
	void PushItem(const char* Item) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(Item);
	}
	void PushItem(int Item) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(Item);
	}
	void PushItem(bool Item) {
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(Item);
	}
	template<typename... T> void PushFn(int Column, int Index, int MenuId, int UniqueId, int Type, int InitialIndex, int IsSelectable, const char* LeftMenuItem, T&&... args) {
		Push(Column, Index, MenuId, UniqueId, Type, InitialIndex, IsSelectable, LeftMenuItem, args...);
	}
private:
	template<typename...T>
	void SetDataSlotFreemodeList(int Index, int Type, int InitialIndex, int IsSelectable, const char* LeftText, T&&... args) {
		FrontendLock l = "SET_DATA_SLOT";
		PushFn(CoronaLobbyColumns::FREEMODE_LIST, Index, 0, Index, Type, InitialIndex, IsSelectable, LeftText, args...);
	}
	bool m_bDoesMenuNeedUpdate = true;
	bool m_bIsMenuActive = false;
	void UpdateMenu() {
		m_bIsMenuActive = HUD::IS_PAUSE_MENU_ACTIVE();
		if (!m_bDoesMenuNeedUpdate && !HUD::IS_FRONTEND_READY_FOR_CONTROL()) { return; }
		{
			const int MenuStyleColor = 167;
			{
				HeaderLock l = "SET_HEADER_TITLE";
				Push("The End", true, "Welcome to the Freemode of the End, A custom gamemode by Unlegitiment.", false);
			}
			{
				HeaderLock l = "SHIFT_CORONA_DESC";
				Push(1, 0);
			}
			{
				HeaderLock l = "SHOW_HEADING_DETAILS";
				Push(false);
			}
			{
				HeaderLock l = "SET_ALL_HIGHLIGHTS";
				Push(1, MenuStyleColor);
			}
			{
				int Color = MenuStyleColor;
				int Rank = 134;
				int RankFreemode = 65;
				const char* PackedTag = "<*0RSG";
				const char* StatusString = "HOST";
				int StatusColor = 20;
				bool ActivateKick = false;
				int SecondIcon = 0;
				FrontendLock l = "SET_DATA_SLOT";

				PushFn(CoronaLobbyColumns::MP_FRIENDS_LIST, 0, 0, 0, FriendsListTypes::AS_ONLINE_IN_SESSION, Rank, 116, "Unlegitiment", Color, 0, 23, RankFreemode, 0, PackedTag, ActivateKick, StatusString, StatusColor, SecondIcon);
			}
			{
				const char* TextureDict = 0, TextureName = 0;
				int Verified = 0;
				bool TransitionInBitMap = 0;
				FrontendLock l = "SET_COLUMN_TITLE";
				Push(CoronaLobbyColumns::FREEMODE_DETAILS, 0, "Fleeca Job - Kuruma", Verified, TextureDict, TextureName, TransitionInBitMap, FreemodeDetailsDisplayTypes::DISPLAY_TYPE_MISSION, 0, "2x", "2x", "", "");
			}
			{
				{
					FrontendLock l = "SET_DATA_SLOT";
					const char* CrewTag = "";
					bool isScIconActive = false;
					PushFn(CoronaLobbyColumns::FREEMODE_DETAILS, 0, 0, 0, FreemodeDetailsTypes::PLAYER_NAME, 0, 0, "Created by", "Rockstar", CrewTag, isScIconActive);
				}
				{
					FrontendLock l = "SET_DATA_SLOT";
					PushFn(CoronaLobbyColumns::FREEMODE_DETAILS, 1, 0, 1, FreemodeDetailsTypes::LIST_ITEM, 0, 0, "Opens at Rank", "12");
				}
				{
					FrontendLock l = "SET_DATA_SLOT";
					PushFn(CoronaLobbyColumns::FREEMODE_DETAILS, 2, 0, 2, FreemodeDetailsTypes::LIST_ITEM, 0, 0, "Players", "2");
				}
				{
					FrontendLock l = "SET_DATA_SLOT";
					bool Checkmark = true;
					PushFn(CoronaLobbyColumns::FREEMODE_DETAILS, 3, 0, 3, FreemodeDetailsTypes::MISSION_ICON, 0, 0, "Type", "Setup", 17, MenuStyleColor, Checkmark);
				}
			}
			{
				bool IsVerified = false;
				int ModeIcon = 0;
				int ColourItem = MenuStyleColor;
				int Index = 20;
				const int NO_COLOR = 0;
				SetDataSlotFreemodeList(0, FreemodeItemType::CYCLE_OPTION_ITEM, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_GAP_ALT, "Difficulty", IsVerified, ModeIcon, "Hard (1.25x RP & Cash)", ColourItem);
				SetDataSlotFreemodeList(1, FreemodeItemType::CYCLE_OPTION_ITEM, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_GAP_ALT, "Heist Clothing", IsVerified, ModeIcon, "From Selection", ColourItem);
				SetDataSlotFreemodeList(2, FreemodeItemType::CYCLE_OPTION_ITEM, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_GAP_ALT, "Outfit Customization", IsVerified, ModeIcon, "Leader Style Choice", ColourItem);
				SetDataSlotFreemodeList(3, FreemodeItemType::CYCLE_OPTION_ITEM, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_GAP_ALT, "Camera Lock", IsVerified, ModeIcon, "None", ColourItem);
				SetDataSlotFreemodeList(4, FreemodeItemType::CYCLE_OPTION_ITEM, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_GAP_ALT, "Weapons", IsVerified, ModeIcon, "Carbine Rifle", ColourItem);
				SetDataSlotFreemodeList(5, 1, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_GAP_ALT, "Purchase Rounds x 60", IsVerified, ModeIcon, "Full", ColourItem);
				SetDataSlotFreemodeList(6, 1, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_GAP_ALT, "Purchase Super Heavy Armor", IsVerified, ModeIcon, "Equipped", ColourItem);
			}
			{
				bool IsVerified = false;
				int ModeIcon = 0;
				int SomeColor = 116;
				int ColourItem = 166;
				int Index = 1;
				const int NO_COLOR = 0;
				/*
					Unique Id allows us to get where we are from the natives. Its script defined.
				*/
				SetDataSlotFreemodeList(7, FreemodeItemType::COLOUR_ALL_ITEM, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_GAP_ALT, "Confirm Settings", IsVerified, ModeIcon, "", ColourItem);
			}
			{
				bool IsVerified = false;
				int ModeIcon = 0;
				int SomeColor = 116;
				int ColourItem = 166;
				int Index = 1;
				const int NO_COLOR = 0;
				/*
					Unique Id allows us to get where we are from the natives. Its script defined.
				*/
				SetDataSlotFreemodeList(8, 1, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_NOGAP, "Cash", IsVerified, ModeIcon, "$4,547,474", ColourItem, 0, 0, 1);
				SetDataSlotFreemodeList(9, 1, NO_COLOR, FreemodeItemSelection::IS_SELECTABLE_NOGAP, "Carbine Rifle Ammo", IsVerified, ModeIcon, "9939/60", ColourItem, 0, 0, 0);
			}
			{
				FrontendLock l = "SET_DESCRIPTION";
				Push(CoronaLobbyColumns::FREEMODE_LIST, "Allows you to manually invite Friends, Crew members, previous players or similarly skilled players.", 0, 0);
			}
			for (int i = 0; i < CoronaLobbyColumns::MAX_CARDS; i++) {
				FrontendLock l = FrontendLock("DISPLAY_DATA_SLOT");
				Push(i);
			}
			{
				FrontendLock l = "SET_COLUMN_FOCUS";
				Push(CoronaLobbyColumns::FREEMODE_LIST, 1, 1, 1);
			}
			for (int i = 0; i < 4; i++) {
				FrontendLock l = "DISPLAY_DATA_SLOT";
				scPush((int)i);
			}
			m_bDoesMenuNeedUpdate = false;
		}
	}
	void ActivateMode() {
		STREAMING::SWITCH_TO_MULTI_FIRSTPART(PLAYER::PLAYER_PED_ID(), 0, 1);
		m_bIsSwitchActive = true;
	}
	void UpdateLaunch() {
		if (!this->IsSpActive) return;
		if (IsKeyJustUp(VK_F15)) {
			if (!m_bIsMenuActive) {
				HUD::ACTIVATE_FRONTEND_MENU(MISC::GET_HASH_KEY("FE_MENU_VERSION_CORONA"), false, 0);
			} else {
				HUD::SET_FRONTEND_ACTIVE(false);
			}
			m_bIsMenuActive = !m_bIsMenuActive;
			m_bDoesMenuNeedUpdate = !m_bDoesMenuNeedUpdate;
		}

		UpdateMenu();
		GRAPHICS::DRAW_MARKER(1, TranslateVector(GamemodeMarkerLocation), TranslateVector(legit::Vec3f{0,0,0}), TranslateVector(legit::Vec3f{0,0,0}), TranslateVector(legit::Vec3f{4.75,4.75,1}), GamemodeColor.r, GamemodeColor.g, GamemodeColor.b, GamemodeColor.a, false, true, 0, false, 0, 0, false);
		if (GetPlayerCoord().Distance(GamemodeMarkerLocation) < 12) {
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(ScaleformIndex, "SET_MISSION_INFO");
			/*
			missionName, missionType, playerInfo, percentage, debugValue, isRockstarVerified, playersRequired, RP, cash, time
			*/
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("TheEnd");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("Freemode");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("100%");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("Solo");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING("");
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			if (GameplayCamera::GetPos().Distance(GamemodeStartLocation) > 1.5) {
				auto v = GameplayCamera::GetRot();
				GRAPHICS::DRAW_SCALEFORM_MOVIE_3D_SOLID(ScaleformIndex, TranslateVector(GamemodeStartLocation.Subtract({0,0,0.5})), TranslateVector(v.ScaleV({0,0,-1})), 1, 1, 1, TranslateVector(legit::Vec3f{4.75,4.75,1}), 0);
			}
			GRAPHICS::DRAW_MARKER(9, TranslateVector(GamemodeMarkerLocation), TranslateVector(legit::Vec3f{0,0,0}), TranslateVector(legit::Vec3f{0,0,0}), TranslateVector(legit::Vec3f{5,5,3}), GamemodeColor.r, GamemodeColor.g, GamemodeColor.b, GamemodeColor.a, false, true, 0, false, TXD, "custom_icon", false);
		}
		if (GamemodeStartLocation.Distance(GetPlayerCoord()) < 2.6f && !m_bIsSwitchActive) {
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("FMMC_STRT_JB");
			HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 0, 0);
			if (PAD::IS_CONTROL_JUST_RELEASED(0, 51)) {
				ActivateMode();
			}
		}
		if (IsKeyJustUp(VK_F16)) {
			EntityHelpers::SetCoords(PLAYER::PLAYER_PED_ID(), {0,0,100});
			modInfof("Start teleport\n");
		}
		if (IsKeyJustUp(VK_DIVIDE)) {
			PlayerWarpMgr::Stop();
			modInfof("Player has requested stop for Teleport.");
		}
		SphericalDebug(GamemodeStartLocation, 2.6, {0,0,0,120});
		SphericalDebug(GamemodeStartLocation, 12, {0,0,255,120});
		SphericalDebug(GamemodeMarkerLocation, 0.2, {0,255,0,255});
		SphericalDebug(GamemodeStartLocation, 0.2, {255,0,0,255});
	}
	static void SphericalDebug(legit::Vec3f Start, float fRadi, legit::Colorf Col) {
#ifdef USE_SPHERE
		GRAPHICS::DRAW_MARKER_SPHERE(TranslateVector(Start), fRadi, Col.r, Col.g, Col.b, Col.a);
#else 
		GRAPHICS::DRAW_MARKER(28, TranslateVector(Start), TranslateVector(legit::Vec3f{0,0,0}), TranslateVector(legit::Vec3f{0,0,0}), TranslateVector(legit::Vec3f{fRadi, fRadi, fRadi}), Col.r, Col.g, Col.b, Col.a, 0, 0, 0, 0, 0, 0, 0);
#endif
	}
	static void DrawLine() {}
	static void BoxVisual(legit::Vec3f Start, float Scale, legit::Colorf Col) {
		GRAPHICS::DRAW_BOX(TranslateVector(Start.Subtract({Scale,Scale,Scale})), TranslateVector(Start.Add({Scale,Scale,Scale})), Col.r, Col.g, Col.b, Col.a);
	}
	static void RequestTXD() {
		while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(TXD)) {
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(TXD, 1);
			WAIT(0);
		}
	}
	static legit::Vec3f GetPlayerCoord() {
		return TranslateVector(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1));
	}
	static legit::Vec3f TranslateVector(const Vector3& vec) {
		return {vec.x, vec.y, vec.z};
	}
	static Vector3 TranslateVector(const legit::Vec3f& vec) {
		return legit::Promote(vec);
	}
	legit::Colorf GamemodeColor = {93, 182, 229, 255};
	legit::Vec3f GamemodeStartLocation;
	legit::Vec3f GamemodeMarkerLocation;
	bool IsSpActive = true;
};

class CMod {
public:
	static void Init() {
		modInfof("--Mod Init Begin--\n\n");
		CPlayerSwitch::Init();
		gtaPlayerMgr::Init();
		legit::netLogger::Send("\n");
		//sm_pFreemodePtr = new CFreemode();
		CTheCreator::Init();
		modInfof("--Mod Init End  --\n\n");
		float fAspectRatio = GRAPHICS::GET_SCREEN_ASPECT_RATIO();
		modInfof("Aspect Ratio: %f\n", fAspectRatio);
	}
	static void Update() {
		CPlayerSwitch::Update();
		gtaPlayerMgr::Update();
		//sm_pFreemodePtr->Update();
		CTheCreator::Update();
		if (IsKeyJustUp(VK_NUMPAD0)) {
			for (const auto& a : ScriptThreadController::GetSet()) {
				modInfof("Script %d(%s) is in Set.\n", a, SCRIPT::GET_NAME_OF_SCRIPT_WITH_THIS_ID(a));
			}
		}
	}
	static void Shutdown() {
		CTheCreator::Shutdown();
		//delete sm_pFreemodePtr;
		gtaPlayerMgr::Shutdown();
		CPlayerSwitch::Shutdown();
	}
	static inline CFreemode* sm_pFreemodePtr = nullptr;
};