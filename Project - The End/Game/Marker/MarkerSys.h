#pragma once
#include <Project - The End\Game\GameEntities\Markers.h>
#include <Project - The End\Game\Gameplay.h>
#include <Project - The End\Game\Renderer\Renderer.h>
#include "MarkerRet.h"
class CMarkerMgr {
public:
	MarkerReturn Create(sMarkerData data) {
		CMarker* m_Marker = new CMarker();
		m_Marker->GetData() = data;
		CGameplay::GetRenderer()->Add(m_Marker->GetRenderMtl());
		MarkerReturn m;
		m.m_pMarker = m_Marker;
		m.m_UpdateMarker = nullptr;
		m_Markers.push_back(m);
		return m;
	}
	void AddMarker(MarkerReturn m) {
		this->m_Markers.push_back(m);
	}
	void Remove(CMarker* marker) {
		for (auto it = m_Markers.begin(); it != m_Markers.end(); it++) {
			if (it->m_pMarker == marker) {
				delete it->m_pMarker;
				m_Markers.erase(it);
				break;
			}
		}
	}
	void RemoveFromList(MarkerReturn marker) {
		for (auto it = m_Markers.begin(); it != m_Markers.end(); it++) {
			if (it->m_pMarker == marker.m_pMarker) {
				m_Markers.erase(it);
				break;
			}
		}
	}
	void Update() {
		for (auto& marker : m_Markers) {
			if (marker.m_UpdateMarker) {
				marker.m_UpdateMarker(marker.m_pMarker);
			}
		}
	}
private:
	std::vector<MarkerReturn> m_Markers;
};