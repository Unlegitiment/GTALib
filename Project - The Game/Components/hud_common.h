#pragma once
#include <Project - The End\Logging\EndLogger.h>

CHANNEL_COLOR(HUD, RHIPurple);
#define hudLogf(fmt, ...) __LAG_LOGF__(HUD, "[HUD]" fmt, ##__VA_ARGS__)
#define hudWarnf(fmt, ...) __LAG_WARNF__(HUD, "[HUD]" fmt, ##__VA_ARGS__)