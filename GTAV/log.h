#pragma once
#include <ModCore/logger/netLog.h>
#include <ModCore/terminalColor.h>
#define gtaInfof(msg, ...) FMT_LOG(RGreen "[INFO][GTA][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define gtaWarnf(msg, ...) FMT_LOG(RYellow "[WARNING][GTA][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)
#define gtaErrorf(msg, ...) FMT_LOG(RHIRed "[ERROR][GTA][@%s] ", msg RNorm, __FUNCTION__, __VA_ARGS__)