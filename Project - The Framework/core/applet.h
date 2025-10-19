#pragma once
#include <vector>	
class fwApplet {
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void AddUpdate(void(*Method)()) {
		this->m_Functors.push_back(Method);
		return;
	}
	virtual void RemoveUpdateFunctor(void(*Method)()) {
		auto r = std::find(m_Functors.begin(), m_Functors.end(), Method);
		if (r == m_Functors.end()) return;
		m_Functors.erase(r);

	}
	virtual void Shutdown() = 0;
	static fwApplet* Get() {
		return m_Applet;
	}
protected:
	std::vector<void(*)()> m_Functors;
	static inline fwApplet* m_Applet = nullptr;
};