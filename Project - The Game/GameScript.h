#pragma once
#include <vector>
#include <string>
#include "SHV/natives.h"
#include <Project - The Framework\ExpandedExpressions\BoundedWhile.h>
#include <Project - The Framework\Timer.h>

#include "../Project - The End/Logging/EndLogger.h"

CHANNEL_COLOR(SCRIPT, RBlue);
#define scriptLogf(fmt, ...) __LAG_LOGF__(SCRIPT, "[SCRIPT] " fmt, __VA_ARGS__);

class GameScripts {
	class GameScriptTimer : public fwTimer<int> {
	public:
		GameScriptTimer(Type addative) : fwTimer<int>(addative, MISC::GET_GAME_TIMER){
		}
	};
public:
	struct Script {
		std::string m_ScriptName;
		int m_ScriptId;
	};
	static constexpr int MAX_ATT = 10;
	static constexpr int TIMEOUT_MAX = 10000;
	static void Init() {
		sm_Timer = new GameScriptTimer(TIMEOUT_MAX);
		Scan();
	}
	static bool IsScriptActive(const char* name) {
		for (auto& script : sm_Scripts) {
			if (script.m_ScriptName == name) {
				return true;
			}
		}
		return false;
	}
	static bool IsScriptActive(int id) {
		for (auto& script : sm_Scripts) {
			if (script.m_ScriptId == id) {
				return true;
			}
		}
		return false;
	}
	static void Launch(Script s, int RequestedStackSize) {
		SCRIPT::REQUEST_SCRIPT(s.m_ScriptName.c_str());
		auto Bond = BoundedWhile([&]{ return !SCRIPT::HAS_SCRIPT_LOADED(s.m_ScriptName.c_str()); }, MAX_ATT, [&](bool cond, int att)->void {
			if (!cond) {
				WAIT(0);
			}
			else {
				SYSTEM::START_NEW_SCRIPT(s.m_ScriptName.c_str(), RequestedStackSize);
				sm_Scripts.push_back(s);
			}
			});
	}
	static void TerminateScript(const char* name) {
		for (auto it = sm_Scripts.begin(); it != sm_Scripts.end(); ++it) {
			if (it->m_ScriptName == name) {
				SCRIPT::TERMINATE_THREAD(it->m_ScriptId);
				sm_Scripts.erase(it);
				break;
			}
		}
	}
	static void TerminateScript(int ThreadId) {
		for (auto it = sm_Scripts.begin(); it != sm_Scripts.end(); ++it) {
			if (it->m_ScriptId == ThreadId) {
				SCRIPT::TERMINATE_THREAD(it->m_ScriptId);
				sm_Scripts.erase(it);
				break;
			}
		}
	}
	static void TerminateAllScripts() {
		for (auto it = sm_Scripts.begin(); it != sm_Scripts.end(); ) {
			SCRIPT::TERMINATE_THREAD(it->m_ScriptId);
			++it;
		}
		sm_Scripts.clear(); // they'd all be dead anyways lmao.
	}
	static void TerminateAllScriptsNonSHV() {
		for (auto& it : sm_Scripts) {
			if (MISC::GET_HASH_KEY(it.m_ScriptName.c_str()) != SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME()) { // right now all SHV threads use "AudioTest" as a script pseudoname but else it could be bad lmao.
				SCRIPT::TERMINATE_THREAD(it.m_ScriptId);
			}
		}
		sm_Scripts.clear();
		Scan();
	}
	static void Update() {
		if (!sm_Timer) {
			return; // throw a fit. 
		}
		if (sm_Timer->HasElapsed()||sForceRescan) {
			if (sForceRescan) sForceRescan = false; else sm_Timer->Reset();
			sm_Scripts.clear();
			Scan();
		}
	}
	static void Scan() {
		SCRIPT::SCRIPT_THREAD_ITERATOR_RESET();
		int ThreadId = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
		while (SCRIPT::IS_THREAD_ACTIVE(ThreadId)) {
			Script s;
			s.m_ScriptId = ThreadId;
			s.m_ScriptName = SCRIPT::GET_NAME_OF_SCRIPT_WITH_THIS_ID(ThreadId);
			sm_Scripts.push_back(s);
			scriptLogf("[%s, %d] Script Loaded", s.m_ScriptName.c_str(), s.m_ScriptId);
			ThreadId = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID(); 
		}
		scriptLogf("Scan Complete #Scripts: %d", sm_Scripts.size());

	}
	static void Shutdown() {
		if (sm_Timer) { delete sm_Timer; sm_Timer = nullptr; }
	}
	static const std::vector<Script>& GetScripts() { return sm_Scripts; }
	static inline bool sForceRescan = false;
private:
	static inline GameScriptTimer* sm_Timer = nullptr;
	static inline std::vector<Script> sm_Scripts;
};