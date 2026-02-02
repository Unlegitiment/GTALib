#pragma once
#include <GTAV/log.h>
#include <ModCore/thirdparty/ScriptHook/include/natives.h>
#include <unordered_set>
class ScriptThreadController {
public:
	static void Init() {
		SCRIPT::SCRIPT_THREAD_ITERATOR_RESET();
		int iter = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
		while (SCRIPT::IS_THREAD_ACTIVE(iter)) {
			if (m_Set.insert(iter).second) {
				gtaInfof("Thread Controller added %d(%s)\n", iter, SCRIPT::GET_NAME_OF_SCRIPT_WITH_THIS_ID(iter));
			}
			iter = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
		}
	}
	static int LaunchThread(const char* Name, size_t StackSize) {
		SCRIPT::REQUEST_SCRIPT(Name);
		while (!SCRIPT::HAS_SCRIPT_LOADED(Name)) {
			gtaInfof("Script loading %s with Stack Size: %llu", Name, StackSize);
			WAIT(0);
		}
		int x = BUILTIN::START_NEW_SCRIPT(Name, StackSize);
		m_Set.insert(x);
		return x;
	}
	static const std::unordered_set<int>& GetSet() {
		return m_Set;
	}
	static void Update() {
		SCRIPT::SCRIPT_THREAD_ITERATOR_RESET();
		int iter = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
		while (SCRIPT::IS_THREAD_ACTIVE(iter)) {
			if (m_Set.insert(iter).second) {
				gtaInfof("Thread was created from another method. Thread Info: %d, %s\n", iter, SCRIPT::GET_NAME_OF_SCRIPT_WITH_THIS_ID(iter));
			}
			iter = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
		}
		for (auto it = m_Set.begin(); it != m_Set.end(); ) {
			if (!SCRIPT::IS_THREAD_ACTIVE(*it)) {
				gtaInfof("Script Terminated by other means(%d)\n", *it);
				it = m_Set.erase(it);
			}
			else {
				++it;
			}
		}
		
	}
	static void KillScript(int thread) {
		SCRIPT::TERMINATE_THREAD(thread);
		if (m_Set.erase(thread)) {
			gtaInfof("Killed thread with ID: %d", thread);
		}
	}
	static void TerminateSP() {
		SCRIPT::SCRIPT_THREAD_ITERATOR_RESET();
		int thread = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
		Hash h = SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME();
		while (SCRIPT::IS_THREAD_ACTIVE(thread)) {
			if (h != MISC::GET_HASH_KEY(SCRIPT::GET_NAME_OF_SCRIPT_WITH_THIS_ID(thread))) {
				KillScript(thread);
			}
			else {
				gtaInfof("Skipping thread with ID %d, it is either our Script or another mod.\n", thread);
			}
			thread = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
			WAIT(0);
		}
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
	static inline std::unordered_set<int> m_Set;
};