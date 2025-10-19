#pragma once
#include <functional>
class BoundedWhile {
public:
	using Predicate = std::function<bool()>;
	using Functor = std::function<void(bool, int)>;
	Predicate Condition;
	int MaxConditionBounds = 1;
	Functor m_Function;
	BoundedWhile(Predicate Cond, int Max, Functor Func) {
		this->MaxConditionBounds = Max;
		this->Condition = Cond;
		this->m_Function = Func;
		Update();
	}
	void Update() {
		while (Condition() && CurrentBounds < MaxConditionBounds) {
			CurrentBounds++;
			m_Function(Condition(), CurrentBounds);
		}
	}
	int GetCurrentIteration() {
		return CurrentBounds;
	}
private:
	int CurrentBounds = 0;
};
