#pragma once
#include <Project - The Framework\math\color.h>
#include <Project - The Framework\math\vec3.h>
#include <Project - The Game\SHV\natives.h>
#include <Project - The Game\SHV\enums.h>
#include <Main\keyboard.h>
#include <string>
#include <Project - The End/Logging/EndLogger.h>
#include <vector>
#include <functional>
#include <Project - The Game/Game/Player/Switch/PlayerSwitch.h>
#include <stack>

class CPlayerHelper {
public:
	static int GetPlayerHandle() { return PLAYER::PLAYER_ID(); }
	static int GetPlayerPed() { return PLAYER::PLAYER_PED_ID(); }
	static CVector3 GetPlayerPosition() { return ENTITY::GET_ENTITY_COORDS(GetPlayerPed(), 1); }
	static void SetPlayerPosition(CVector3 v) { ENTITY::SET_ENTITY_COORDS(GetPlayerPed(), v.GetX(), v.GetY(), v.GetZ(), 1, 0, 0, 1); }
	static void SetPlayerHeading(float fHeading) { ENTITY::SET_ENTITY_HEADING(GetPlayerPed(), fHeading); }
	static float GetPlayerHeading() { return ENTITY::GET_ENTITY_HEADING(GetPlayerPed()); }
};
class TheEnd {
public:
	struct sMarkerDef {
		int Type;
		CVector3 Pos;
		CVector3 Rot;
		CVector3 Scale;
		CVector3 Dir;
		Color32 col;
		bool bobUpAndDown = false;
		bool faceCam = true;
		int p19 = 0;
		bool Rotate = false;
		const char* TextureDict = 0;
		const char* TextureName = 0;
		bool Invert = false;
	};
	struct Stat {
		enum eStatCharacter {
			SP0,
			SP1,
			SP2,
			MP0,
			MP1,
		};
		struct Date {
			Date(int year, int month, int day, int hour, int minute, int second) 
				: year(year), month(month), day(day),hour(hour),minute(minute),second(second)
			{

			}
			int year;
			int month;
			int day;
			int hour;
			int minute;
			int second;
			int millisecond = 0;
		};
		Stat(const char* name) : m_Name(name) {

		}
		Stat(const char* name, int m_StatSetDefault) : m_Name(name){
			Logger::Writeln("Full statisitic Debug, Name: %s(Hash: %d, FullName:%s), Value: %d", m_Name, GetHash(), GetString().c_str(), m_StatSetDefault);
			Set(m_StatSetDefault);
		}
		/*
		{ "MPPLY_TOTAL_EVC", 534'277'820 } 
		{ "MPPLY_TOTAL_SVC", 317'138'910 } 
		*/
		Stat(const char* name, int m_DefaultStat, bool isCharacterStat) : m_Name(name), isCharacterStat(isCharacterStat) {
			Logger::Writeln("Did not set stat yet!");
			Logger::Writeln("Full statisitic Debug, Name: %s(Hash: %d, FullName:%s), Value: %d", m_Name, GetHash(), GetString().c_str(), m_DefaultStat);
			Set(m_DefaultStat);
		}

		std::string GetCharacterPrefix() {
			switch (CharacterSelection) {
				case SP0:
				case SP1:
				case SP2:
				case MP0:
				case MP1:
					return "MP1";
			}
		}
		template<typename T>
		void Set(T data) {
			Logger::Writeln(RYellow"[WARN]" "Current Stat Type for Setting not supported.");
		}
		template<> void Set(int data) {
			STATS::STAT_SET_INT(GetHash(), data, SaveAfter);
		}		
		template<> void Set(Date data) {
			Date rDate = data;
			STATS::STAT_SET_DATE(GetHash(), (Any*)&rDate, 7, SaveAfter);
		}
		template<typename T> T Get() {

		}
		std::string GetString() {
			std::string mRet;
			if (isCharacterStat) {
				mRet = GetCharacterPrefix();
				mRet.append("_");
			}
			mRet.append(m_Name); // Does this work if the string is empty?
			return mRet;
		}
		Hash GetHash() {
			return MISC::GET_HASH_KEY(GetString().c_str());
		}
		eStatCharacter CharacterSelection = MP1;
		bool isCharacterStat = true;
		const char* m_Name;
		bool SaveAfter = true;
	};
	template<typename T>
	class baseTimeFetchRequest {
	public:
		virtual T GetHour() = 0;
		virtual T GetMinute() = 0;
		virtual T GetSecond() = 0;
	};
	template<typename T>
	class baseDateRequest {
	public:
		virtual T GetYear() = 0;
		virtual T GetMonth() = 0;
		virtual T GetDayOfMonth() = 0;
		virtual T GetDayOfWeek() = 0; 
	};
	class CGTAVDateFetch : public baseDateRequest<int>{
	public:
		int GetMonth() {
			return CLOCK::GET_CLOCK_MONTH();
		}
		int GetDayOfMonth() {
			return CLOCK::GET_CLOCK_DAY_OF_MONTH();
		}
		int GetDayOfWeek() {
			return CLOCK::GET_CLOCK_DAY_OF_WEEK();
		}
		int GetYear() {
			return CLOCK::GET_CLOCK_YEAR();
		}
	};
	class CGTATimeFetch : public baseTimeFetchRequest<int> {
		// Inherited via baseTimeFetchRequest
		int GetHour() override
		{
			return CLOCK::GET_CLOCK_HOURS();
		}
		int GetMinute() override
		{
			return CLOCK::GET_CLOCK_MINUTES();
		}
		int GetSecond() override
		{
			return CLOCK::GET_CLOCK_SECONDS();
		}
	};
	struct sTimeStamp {
		int Hour;
		int Minute;
		int Second;
		static sTimeStamp Now(baseTimeFetchRequest<int>* fRequest) {
			sTimeStamp m_Stamp{};
			m_Stamp.Hour = fRequest->GetHour();
			m_Stamp.Minute = fRequest->GetMinute();
			m_Stamp.Second = fRequest->GetSecond();
			return m_Stamp;
		}
		static sTimeStamp Now() {
			CGTATimeFetch reqType = CGTATimeFetch();
			return Now(&reqType);
		}
	};
	class Phone {
	public:
		enum class PhoneIcon : int
		{
			CAMERA = 1,
			TEXT_MESSAGE = 2,
			CALENDAR = 3,
			EMAIL = 4,
			CALL = 5,
			EYEFIND = 6,
			MAP = 7,
			APPS = 8,
			MEDIA = 9,
			ATTACHMENT = 10,
			NEW_CONTACT = 11,
			SIDE_TASKS = 12,
			BAWSAQ = 13,
			MULTIPLAYER = 14,
			MUSIC = 15,
			GPS = 16,
			SPARE = 17,
			RINGTONE = 18,
			TEXT_TONE = 19,
			VIBRATE_ON = 20,
			VIBRATE_OFF = 21,
			VOLUME = 22,
			SETTINGS_1 = 23,
			SETTINGS_2 = 24,
			PROFILE = 25,
			SLEEP_MODE = 26,
			MISSED_CALL = 27,
			UNREAD_EMAIL = 28,
			READ_EMAIL = 29,
			REPLY_EMAIL = 30,
			REPLAYMISSION = 31,
			SHITSKIP = 32,
			UNREAD_SMS = 33,
			READ_SMS = 34,
			PLAYER_LIST = 35,
			COP_BACKUP = 36,
			GANG_TAXI = 37,
			REPEAT_PLAY = 38,
			CHECKLIST = 39,
			SNIPER = 40,
			ZIT_IT = 41,
			TRACKIFY = 42,
			SAVE = 43,
			ADD_TAG = 44,
			REMOVE_TAG = 45,
			LOCATION = 46,
			PARTY = 47,
			TICKED = 48,
			BROADCAST = 49,
			GAMEPAD = 50,
			SILENT = 51,
			INVITES_PENDING = 52,
			ON_CALL = 53,
			H_LOCK = 54,
			PUSH_TO_TALK = 55,
			BENNYS = 56,
			GANG = 57,
			TRACKER = 58,
			SIGHT_SEER = 59,
			BEACON = 60,
			VINEWOOD = 61,
			DARNELL = 62
		};


	};
	class CSCLHelper {
	public:
		//Yuck!
#define __SCL_DEF(__Type, __Func) \
		template<> static void Call<__Type>(__Type data) { __Func(data); /*Logger::Writeln("Type: %s", typeid(__Type).name());*/ }
		template<typename T> static void Call(T data) {
			Logger::Writeln("Cannot do type %s", typeid(data).name());
		}
		__SCL_DEF(int, GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT);
		__SCL_DEF(const char*, GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING);
		__SCL_DEF(float, GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT);
		__SCL_DEF(bool, GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL);
		template<> static void Call<char[]>(char data[]) {
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(data); 
		}
#undef __SCL_DEF
	private:

	};
	class CFrontendMenu {
	public:
		template<typename... T> static void Header(const char* Method, T&&... args) {
			//Logger::Writeln("-----Beginning Header-Method: %s-----", Method);
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER(Method);
			(CSCLHelper::Call(std::forward<T>(args)), ...);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			//Logger::Writeln("-----Ending Header-Method: %s-----", Method);
		}
		template<typename... T> static void FrontEnd(const char* Method, T&&... args) {
			//Logger::Writeln("-----Beginning Frontend-Method: %s-----", Method);
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND(Method);
			(CSCLHelper::Call(std::forward<T>(args)), ...);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			//Logger::Writeln("-----Ending Frontend-Method: %s-----", Method);
		}
		CFrontendMenu(Hash iMenuHash, bool Open, bool Pause = false) : m_iMenuHash(iMenuHash), m_bPauseGameWhilstOpen(Pause){
			if (Open) {
				OpenMenu();
			}
		}
		void OpenMenu() {
			OpenToComponent(0);
		}
		void OpenToComponent(int Component) {
			HUD::ACTIVATE_FRONTEND_MENU(m_iMenuHash, m_bPauseGameWhilstOpen, Component);
			m_bOpen = true;
		}
		bool IsOpen() const { return this->m_bOpen; }
		void CloseMenu() {
			HUD::SET_FRONTEND_ACTIVE(0);
			m_bOpen = false;
		}
	private:
		Hash m_iMenuHash = 0;
		bool m_bOpen = false;
		bool m_bPauseGameWhilstOpen = false;
	};
	class CPauseMenu {
	public:
		static void Init() {
			sm_FrontendMenu = new CFrontendMenu(MISC::GET_HASH_KEY("FE_MENU_VERSION_MP_PAUSE"), false);
		}
		static bool IsPauseKeyJustReleased() {
			return PAD::IS_DISABLED_CONTROL_JUST_RELEASED(2, 199) || PAD::IS_DISABLED_CONTROL_JUST_RELEASED(2, 200);
		}
		static bool IsMenuKeyClosePressed() {
			return IsKeyJustUp(VK_ESCAPE) || IsKeyJustUp(VK_BACK) || IsPauseKeyJustReleased(); // Have to check for mouse Right Up.
		}
		static CFrontendMenu* GetMenu() { return sm_FrontendMenu; } 
		static void UpdateMenuOpen() {
			Logger::Writeln("UpdateMenuOpen");
			sm_FrontendMenu->Header("SET_HEADING_DETAILS", "Character", "Date", "Money", 0);
			sm_FrontendMenu->Header("SET_HEADER_TITLE", "Grand Theft Auto V", 1, "", 0);
			sm_FrontendMenu->Header("SHIFT_CORONA_DESC", 0, 1);

			//Vector3 v = HUD::GET_PAUSE_MENU_POSITION(); // this does not return the Cursor position, It returns menu position? 
			//Logger::Writeln("V: {%f, %f, %f}", v.x, v.y, v.z);
			// This is default stuff.
			sm_FrontendMenu->Header("SHOW_HEADING_DETAILS", true);
			sm_FrontendMenu->FrontEnd("SHOW_MENU", true);
		}
		static void Update() {
			PAD::DISABLE_CONTROL_ACTION(2, 199, 0);
			PAD::DISABLE_CONTROL_ACTION(2, 200, 0); //  These are for the menu.
			switch (sm_FrontendMenu->IsOpen()) {
			case true:
				if (IsMenuKeyClosePressed()) {
					sm_FrontendMenu->CloseMenu();
				}
				UpdateMenuOpen();
				Logger::Writeln("%s" __FUNCTION__);
				break;
			case false:
				if (IsPauseKeyJustReleased()) {
					sm_FrontendMenu->OpenMenu();
				}
				break;

			}
		}
		static void Shutdown() {
			sm_FrontendMenu->CloseMenu();
			delete sm_FrontendMenu;
		}
	private:
		static inline CFrontendMenu* sm_FrontendMenu = nullptr;
		//static inline Blip sm_BlipRes = 0;
	};
	template<typename T> class CFMInitializer : public T {
	public:
		static inline bool HasInitialized = false;
	};
	template<typename T> class CFMStatic : public CFMInitializer<T> {
	public:
		static void Init()
		{
			if (CFMInitializer<T>::HasInitialized) return;
			T::Init();
			CFMInitializer<T>::HasInitialized = true;
		}
		template<typename... Args> static void Init(Args&&... args)
		{
			if (CFMInitializer<T>::HasInitialized) return;
			if constexpr (sizeof...(args) > 0)
			{
				T::Init((std::forward<Args>(args), ...));
			} else {
				T::Init();
			}
			CFMInitializer<T>::HasInitialized = true;
		}
		static void Shutdown()
		{
			if (!CFMInitializer<T>::HasInitialized) return;
			{
				T::Shutdown();
			}
			CFMInitializer<T>::HasInitialized = false;
		}
		template<typename... Args> static void Shutdown(Args&&... args)
		{
			if (!CFMInitializer<T>::HasInitialized) return;
			if (sizeof...(args) > 0)
			{
				T::Shutdown((std::forward<Args>(args), ...)); // You smell.
			}
			else {
				T::Shutdown();
			}
			CFMInitializer<T>::HasInitialized = false;
		}

	};
	class CFMMarker
	{
	public:
		CFMMarker(CVector3 pos)
		{
			while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("mpmissmarkers256"))
			{
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("mpmissmarkers256", 1);
				WAIT(0);
			}
			static float fScaleBase = 5.f;
			const float fLongrangeScale = fScaleBase - 0.2f; // 4.8f;
			sMarkerDef& m_VerticalLongDistance = m_VerticalDef;
			m_VerticalLongDistance.Type = 1;
			m_VerticalLongDistance.Pos = pos;
			m_VerticalLongDistance.Scale = { fLongrangeScale,fLongrangeScale,1 };
			m_VerticalLongDistance.col = { 93, 182, 229, 80 };
			// frick you. 
			sMarkerDef& m_ShortrangeMissionMarker = m_MissionDef;
			m_ShortrangeMissionMarker = m_VerticalLongDistance;
			m_ShortrangeMissionMarker.Type = 8;
			m_ShortrangeMissionMarker.Scale = { fScaleBase,fScaleBase,1 };
			m_ShortrangeMissionMarker.col = { 93, 182, 229, 80 };
			m_ShortrangeMissionMarker.TextureDict = "mpmissmarkers256";
			m_ShortrangeMissionMarker.TextureName = "custom_icon"; // You cannot be serious rn vro :wilted_rose:
		}
		sMarkerDef& GetSkinny()
		{
			return m_VerticalDef;
		}
		sMarkerDef& GetFat()
		{
			return m_MissionDef;
		}
		void Update()
		{
			if (CPlayerHelper::GetPlayerPosition().DistNoZ(GetFat().Pos) <= GetSkinny().Scale.GetX() / 2)
			{
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Press ~INPUT_CONTEXT~ to start Activity.");
				HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 0, 0);
				if (PAD::IS_CONTROL_JUST_RELEASED(0,51))
				{
					CFreemode::Launch();
				}
			}
			Render();
		}
		~CFMMarker()
		{
			GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED("mpmissmarkers256");
		}
	private:
		void Render()
		{
			MaintainResources();
			if (CanSeeSkinny())
			{
				DrawMarker(m_VerticalDef);
			}	
			if (CanSeeFat())
			{
				DrawMarker(m_MissionDef);
			}
		}
		void MaintainResources()
		{
			while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("mpmissmarkers256"))
			{
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("mpmissmarkers256", 1);
				WAIT(0);
			}
		}
		static constexpr float m_fRenderDistanceVerticalLongRange = 250;
		static constexpr float m_fRenderDistanceShortrange = 10;
		bool CanSeeSkinny()
		{
			float fRenderDistance = m_fRenderDistanceVerticalLongRange;
			if (m_fRenderDistanceVerticalLongRange == -1) fRenderDistance = 250.f;
			return CPlayerHelper::GetPlayerPosition().Dist(m_VerticalDef.Pos) <= fRenderDistance;
		}
		bool CanSeeFat()
		{
			float fRenderDistance = m_fRenderDistanceShortrange;
			return CPlayerHelper::GetPlayerPosition().Dist(m_MissionDef.Pos) <= fRenderDistance;
		}
		void DrawMarker(const sMarkerDef& Def) {
			GRAPHICS::DRAW_MARKER(Def.Type,
				Def.Pos.GetX(), Def.Pos.GetY(), Def.Pos.GetZ(),
				Def.Dir.GetX(), Def.Dir.GetY(), Def.Dir.GetZ(),
				Def.Rot.GetX(), Def.Rot.GetY(), Def.Rot.GetZ(),
				Def.Scale.GetX(), Def.Scale.GetY(), Def.Scale.GetZ(),
				Def.col.GetR(), Def.col.GetG(), Def.col.GetB(), Def.col.GetA(),
				Def.bobUpAndDown,
				Def.faceCam,
				Def.p19,
				Def.Rotate,
				Def.TextureDict,
				Def.TextureName,
				Def.Invert
			);
		}
		sMarkerDef m_MissionDef, m_VerticalDef;
	};
	class fwPack
	{
	public:
		virtual ~fwPack() = default;

		virtual void Init()
		{
			
		}
		virtual void Update()
		{
			
		}
		virtual void Shutdown()
		{
			
		}

	private:

	};
	/*
	 * CDLCPackOne. Contains the base layers for the Phone Contacts, Basic Abilities, and such.
	 * This is the fundamentals of the game. 
	 */
	class CDLCPackOne : public fwPack
	{
	public:
		void Init() override
		{
			Logger::Writeln("%s", __FUNCTION__);
		}
		void Update() override
		{
			
		}
		void Shutdown() override
		{
			Logger::Writeln("%s", __FUNCTION__);

		}
	private:

	};
	class CFMPacks
	{
	public:
		void Add(fwPack* p )
		{
			m_Packs.push_back(p);
			p->Init(); 
		} 
		std::vector<fwPack*>& GetPacks() { return m_Packs; }
		void Update()
		{
			for (const auto& p : m_Packs)
			{
				p->Update();
			}
		}
		void Remove(fwPack* p )
		{
			auto res = std::find(m_Packs.begin(), m_Packs.end(), p);
			if (res == m_Packs.end()) return;
			m_Packs.erase(res); // Fuck you.
		}
		void Shutdown()
		{
			for (const auto& p : m_Packs)
			{
				p->Shutdown();
			}
			m_Packs.clear();
		}
	private:
		std::vector<fwPack*> m_Packs;
	};
	class CFMScriptLauncher
	{
	public:
		CFMScriptLauncher(CFMPacks* packs) : m_Packs(packs)
		{
			Add(new CDLCPackOne());
		}
		~CFMScriptLauncher()
		{
			ClearAllPacks();
		}
	private:
		void Add(fwPack* p)
		{
			m_Packs->Add(p);
			m_PackPtr.push_back(p);
		}
		void ClearAllPacks()
		{
			for (auto& p : m_PackPtr)
			{
				m_Packs->Remove(p);
				p->Shutdown();
				delete p;
				p = nullptr;
			}
			m_PackPtr.clear();
		}
		CFMPacks* m_Packs;
		std::vector<fwPack*> m_PackPtr;
	};
	template<typename T>
	class CFMSingleton
	{
	public:
		template<typename... Args>
		static void Init(Args&&... args)
		{
			if constexpr ( sizeof...(args) > 0 )
			{
				sm_pInstance = new T(std::forward<Args>(args)...);
			}
			else
			{
				sm_pInstance = new T();
			}
		}
		static T* Get() { return sm_pInstance; }
		static void Destroy()
		{
			delete sm_pInstance; sm_pInstance = nullptr;
		}
	private:
		static inline T* sm_pInstance = nullptr;
	};
	using Packs = CFMSingleton<CFMPacks>;
	class CFreemode
	{
	private:
		using PackLauncher = CFMSingleton<CFMScriptLauncher>;
		template<typename T>
		static bool FMInit() //short hand
		{
			return CFMInitializer<T>::HasInitialized;
		}
	public:
		enum class eLaunchSequence
		{
			ELS_DORMIT,
			ELS_TRIGGER_SWITCH,
			ELS_LAUNCH_SYSTEMS,
			ELS_COME_DOWN
		};
		enum class eFMStatus
		{
			FMS_NOT_TRIGGERED,
			FMS_GAME,
		};
		static void Init()
		{
			sm_Marker = new CFMMarker({1054.6648, -3208.253, 5.9-0.95}); // gotch ya
			Packs::Init();
		}
		static void UpdatePrelaunchSequence()
		{
			if (sm_FreemodeStatus != eFMStatus::FMS_GAME && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
				sm_Marker->Update();
			}
			if (sm_LaunchSequence == eLaunchSequence::ELS_TRIGGER_SWITCH && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
			{
				STREAMING::SWITCH_TO_MULTI_FIRSTPART(PLAYER::PLAYER_PED_ID(), 0, (int)ePlayerSwitchType::EPST_LONG); // no flag
			}
			if (sm_LaunchSequence == eLaunchSequence::ELS_TRIGGER_SWITCH && STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
			{
				if (STREAMING::GET_PLAYER_SWITCH_STATE() == 5) // check
				{
					sm_LaunchSequence = eLaunchSequence::ELS_LAUNCH_SYSTEMS;
				}
			}
		}
		static void Launch()
		{
			sm_LaunchSequence = eLaunchSequence::ELS_TRIGGER_SWITCH;
		}
		static void LaunchSystems()
		{
			CFMStatic<CPauseMenu>::Init();
			PackLauncher::Init(Packs::Get());
		}
		static void HandlePostLaunchSwitch()
		{
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) return;
			if (sm_LaunchSequence == eLaunchSequence::ELS_LAUNCH_SYSTEMS)
			{
				LaunchSystems();
				sm_LaunchSequence = eLaunchSequence::ELS_COME_DOWN;
				sm_FreemodeStatus = eFMStatus::FMS_GAME;
			}
			if (sm_LaunchSequence == eLaunchSequence::ELS_COME_DOWN) // Right now this is one direction.
			{
				STREAMING::SWITCH_TO_MULTI_SECONDPART(PLAYER::PLAYER_PED_ID()); // reserve;
				sm_LaunchSequence = eLaunchSequence::ELS_DORMIT;
			}
		}
		static void UpdatePostLaunch()
		{
			HandlePostLaunchSwitch();
			if (sm_FreemodeStatus != eFMStatus::FMS_GAME) return;
			if (IsKeyJustUp(VK_F13))
			{
				Logger::Writeln("VK_F13 %s: ResetState Triggered", __FUNCTION__);
				ResetState();
			}
			Packs::Get()->Update();
			CFMStatic<CPauseMenu>::Update(); //yoohoo 
		}
		static void ResetState()
		{
			sm_FreemodeStatus = eFMStatus::FMS_NOT_TRIGGERED;
			sm_LaunchSequence = eLaunchSequence::ELS_DORMIT;
		}
		static void Update()
		{
			UpdatePrelaunchSequence();
			UpdatePostLaunch();
		}
		static void Shutdown()
		{
			CFMStatic<CPauseMenu>::Shutdown();
			PackLauncher::Destroy();
			Packs::Get()->Shutdown();
			Packs::Destroy();
			delete sm_Marker;
		}
	private:
		static inline CFMMarker* sm_Marker = nullptr;
		static inline eLaunchSequence sm_LaunchSequence = eLaunchSequence::ELS_DORMIT; // Fuck you.
		static inline eFMStatus sm_FreemodeStatus = (eFMStatus::FMS_NOT_TRIGGERED);
	};
	static void Init() {
		CFreemode::Init();
	}
	static void Update() {
		CFreemode::Update();
	}
	static void Shutdown() {
		CFreemode::Shutdown();
	}
private:

};