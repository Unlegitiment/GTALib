#pragma once
#include <ModCore/logger/netLog.h>
#include <ModCore/terminalColor.h>
#include <ModCore/thirdparty/ScriptHook/include/natives.h>
#include <GTAV/GTAV.h>
#include <Mod/mod/main.h>

#define appInfof(msg, ...) FMT_LOG(RNorm "[INFO][APP][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define appWarnf(msg, ...) FMT_LOG(RYellow "[WARNING][APP][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define appErrorf(msg, ...) FMT_LOG(RHIRed "[ERROR][APP][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
namespace legit {
	class Application {
	public:
		/*
			Important stuff responsible for Thread Global stuff. things like the logger mainly, live at this level.
		*/
        static void PreInit() {
			legit::netPlatConfig::InitClass();
			legit::netLogger::Init();
        }


        static void PostShut() {
			appInfof("Goodbye!\n");
			legit::netLogger::Shutdown();
			legit::netPlatConfig::ShutdownClass();
        }
		/*
			things that use the natives or shv functionality. this runs actually IN the main thread. and separate from the Win32 base code.
		*/
		static void Init() {
			appInfof("--- Application Init Begin. ---\n\n");
			GTA::Init();
			CMod::Init();
			appInfof("--- Application Init End.   ---\n\n");
		}
		static void Update() {
			GTA::Update();
			CMod::Update();
		}
		static void Destroy() {
			CMod::Shutdown();
			GTA::Shutdown();
		}
	private:
	};

}