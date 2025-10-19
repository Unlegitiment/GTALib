#pragma once
#include <functional>
template<typename T>
class fwTimer {
public:
	using Type = T;
	using Functor = std::function<T()>;
	fwTimer(T Addative, Functor Function) {
		this->m_UpdateTimer = Function;
		StartTime = m_UpdateTimer();
		this->Addative = Addative;
		this->MaxTime = Addative + StartTime;
	}
	virtual void Reset(T newAddative) {
		this->Addative = newAddative;
	}
	virtual void Reset() {
		this->StartTime = this->m_UpdateTimer();
		this->MaxTime = this->StartTime + this->Addative;
	}
	virtual bool HasElapsed() {
		CurrentTime = m_UpdateTimer();
		if (CurrentTime >= MaxTime) {
			return true;
		}
		else {
			return false;
		}
	}
	T GetCurrent() { return this->CurrentTime; }
	T GetAddative() { return this->Addative; }
	T GetStart() { return this->StartTime; }
	T GetMax() { return this->MaxTime; }
protected:
	Functor m_UpdateTimer;
private:
	T CurrentTime = 0; 
	T MaxTime;
	T StartTime = 0;
	T Addative = 0;
};