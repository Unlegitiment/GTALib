#pragma once
#include <Project - The Game\SHV\natives.h>
#include <Project - The Framework\core\applet.h>
#include "../Main/ScriptHookFix.h"
#include "Logging\EndLogger.h"
class CModification : public fwApplet{
public:
	using UpdateF = void(*)();
	static void Run() {
		
		m_Applet = new CModification();
		ProcessTerminate = [&]()->void {
			Logger::Writeln("First ProcessTerminate");
			m_Applet->Shutdown();
			delete m_Applet;
			m_Applet = nullptr;
			};
		m_Applet->Init();
		while (true) {
			if (g_ProcessShutdownTriggered) break;
			m_Applet->Update();
			WAIT(0);
		}
	}

	// Inherited via fwApplet
	void Init() override;

	void Update() override;

	void Shutdown() override;
private:

};