#include "TransitionTest.h"
#include <Main\keyboard.h>

void CTransitionTest::Update()
{
	m_Mgr->Update();
	if (IsKeyJustUp(VK_F15)) {
		m_Mgr->Begin(PLAYER::PLAYER_PED_ID());
	}
	if (IsKeyJustUp(VK_F16)) {
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0, 0, 75.0f, 1, 0, 0, 1);
		m_Mgr->End(PLAYER::PLAYER_PED_ID());
	}
}
