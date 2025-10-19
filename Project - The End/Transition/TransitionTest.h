#pragma once
#include <Project - The End\Debug\DbgModule.h>
#include "Transition.h"
class CTransitionTest : public IDebugClass {
public:
	CTransitionTest(CTransitionManager* mgr) :m_Mgr(mgr){ }
	// Inherited via IDebugClass
	void Update() override;
private:
	CTransitionManager* m_Mgr;
};