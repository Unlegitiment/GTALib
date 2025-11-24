#include "App.h"
#include <Project - The Game\GTAVProcess.h>
#include "Logging\EndLogger.h"
#include "Game\TheEnd.h"
// Inherited via fwApplet
void CModification::Init()
{
	const char* INIT_BEGIN = R"(
+-------------------------- STARTING THE END ---------------------------+
+-----------------------------------------------------------------------+
)";

	CNetworkInit::InitWSA();
	Logger::Init();
	Logger::Writeln(INIT_BEGIN);
	GTAV::Init();
	TheEnd::Init();


	this->AddUpdate(TheEnd::Update);
	this->AddUpdate(GTAV::Update);
	Logger::Writeln("INIT_OVER");
}

void CModification::Update()
{
	for (auto a : m_Functors) {
		a();
	}
}

void CModification::Shutdown()
{
	TheEnd::Shutdown();
	GTAV::Shutdown();
	Logger::Shutdown();
}
