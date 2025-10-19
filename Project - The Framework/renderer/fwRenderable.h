#pragma once
#include <Project - The End\Logging\EndLogger.h>

CHANNEL_COLOR(Renderer, RGreen);
#define renderLogf(fmt, ...) __LAG_LOGF__(Renderer, "[RENDERER] " fmt, ##__VA_ARGS__);
class fwRenderable {
public:
	virtual void Render() = 0;
	virtual ~fwRenderable() = default;
};