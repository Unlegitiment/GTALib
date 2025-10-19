#pragma once
#include <Project - The End\Game\GameEntities\Markers.h>
struct MarkerReturn {
	CMarker* m_pMarker = nullptr;
	std::function<void(CMarker*)> m_UpdateMarker;
};