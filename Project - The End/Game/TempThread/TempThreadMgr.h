#pragma once
#include <vector>
#include "TempThread.h"
class CTempThreadMgr {
public:
	CTempThreadMgr() = default;
	void AddThread(CTempThread* thread) {
		m_Threads.push_back(thread);
	}
	void Update() {
		std::vector<std::vector<CTempThread*>::iterator> ClearThreads;
		for (auto it = m_Threads.begin(); it != m_Threads.end(); it++) {
			if ((*it)->Update()) {
				ClearThreads.push_back(it);
				(*it)->m_WasThreadCompleted = true;
				(*it)->onC();
			}
		}
		for (auto res : ClearThreads) {
			m_Threads.erase(res);
		}
	}
private:
	std::vector<CTempThread*> m_Threads;
};