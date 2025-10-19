#pragma once
#include "Project - The Game\SHV\natives.h"
class HelpView {
public:

	HelpView(const HelpModel* model) :m_Model(model){

	}
	void Render() {
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(m_Model->Get().c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(m_Model->m_iID, m_Model->m_bLoopDisplay, m_Model->m_bShouldBeep, m_Model->m_iStyle);
	}
private:
	const HelpModel* m_Model = nullptr;
};