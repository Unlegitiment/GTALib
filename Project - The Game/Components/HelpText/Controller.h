#pragma once
#include "Model.h"
#include "View.h"
class HelpController {
public:
	HelpController(HelpModel* model, HelpView* view) :m_Model(model), m_View(view){

	}
	void ChangeText(std::string m_text) {
		m_Model->SetString(m_text);
	}
	void ActivateDisplay(bool beep) {
		this->m_Model->m_bShouldBeep = beep;
		m_bShouldDisplay = true;
	}
	void DeactivateDisplay() {
		m_bShouldDisplay = false;
	}
	bool IsDisplayActive() {
		return this->m_bShouldDisplay;
	}
	void Update() {
		if (m_bShouldDisplay) {
			m_View->Render();
		}
	}
private:
	HelpModel* m_Model;
	HelpView* m_View;
	bool m_bShouldDisplay = false;
};