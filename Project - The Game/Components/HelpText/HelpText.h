#pragma once
#include "Controller.h"
class CHelpText {
public:
	CHelpText() : m_View(&m_Model), m_Controller(&m_Model, &m_View){
		
	}
	HelpController& GetController() {
		return m_Controller;
	}
private:
	HelpModel m_Model;
	HelpController m_Controller;
	HelpView m_View;
};