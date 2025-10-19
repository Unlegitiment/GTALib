#pragma once
#include <functional>
class CTempThread {
public:
	using cb = std::function<void()>;

	friend class CTempThreadMgr;
	void OnComplete(cb c) {
		onC = std::move(c);
	}
	virtual bool Update() = 0;
	virtual ~CTempThread() = default;
	bool WasTaskCompleted() { return m_WasThreadCompleted; }
private:
	bool m_WasThreadCompleted = false;
	cb onC;
};