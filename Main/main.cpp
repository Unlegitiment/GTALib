/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/
#include <Mod/App.h>
#include "ModCore/thirdparty/ScriptHook/include/main.h"
#include "script.h"
#include "keyboard.h"
#define sysInfof(msg, ...) FMT_LOG(RHIPurple "[INFO][SYS][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define sysWarnf(msg, ...) FMT_LOG(RYellow "[WARNING][SYS][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define sysErrorf(msg, ...) FMT_LOG(RHIRed "[ERROR][SYS][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define sysFatalf(msg, ...) FMT_LOG(RRed "[FATAL][SYS][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
/*
	BUG! Upon a crash of the host application, ScriptHookV does not handle this nicely and does not call Detach. Look into alternative methods.
	BUG! Upon changing the size of the DLL (code changes or the like) SHV upon reload Summons the Thread's Process and then fails to start the thread. - Req steps: Unload SP Scripts (main, main_persist etc.) Reload All Active Scripts (meaning all SHV ones). Result: Game Crash.
		We are likely reaching the ends of what ScriptHookV will allow for us to do. Consider a custom DLL loader or proc hijack?
*/
static bool AreScriptsInitialized = false;
BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		legit::Application::PreInit();
		scriptRegister(hInstance, ScriptMain);
		keyboardHandlerRegister(OnKeyboardMessage);
		sysInfof("Reason = process ATTACH.\n");
		break; 
	case DLL_THREAD_ATTACH:
		sysInfof("Reason = Thread ATTACH.\n");
		break;
	case DLL_THREAD_DETACH:
		sysInfof("Reason = Thread DETACH.\n");
		break;
	case DLL_PROCESS_DETACH:
		if (lpReserved != nullptr) {
			sysInfof("Script's host process terminated.\n");
			break; // do not do cleanup if process termination scenario.
		}
		scriptUnregister(hInstance);
		keyboardHandlerUnregister(OnKeyboardMessage);
		sysInfof("Reason = Process Detach.\n");
		legit::Application::PostShut();
		break;
	}		
	return TRUE;
}