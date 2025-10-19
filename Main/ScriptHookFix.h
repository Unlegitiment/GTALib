#pragma once
#include <functional>
static bool g_ProcessShutdownTriggered = false;
#include "../Project - The End/Logging/EndLogger.h"
static std::function<void()> ProcessTerminate = []()->void {
	Logger::Writeln("Default ProcessTerminate. There is not one specified!");
	Logger::Shutdown();
};