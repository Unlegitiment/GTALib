#pragma once
#include <string>
class HelpModel {
public:
	HelpModel() {

	}
	void SetString(std::string Text) {
		m_Text = Text;
	}
	void Clear() {
		m_Text.clear();
	}
	std::string Get() const { return this->m_Text; }
	bool m_bShouldBeep = false;
	int m_iStyle = -1;
	int m_iID = 0;
	bool m_bLoopDisplay = false;

private:
	std::string m_Text;
};