#pragma once
#include "Project - The Framework/renderer/fwRenderable.h"
#include "Project - The Framework/math/vec3.h"
#include "Project - The Framework/math/color.h"
#include <string>


class CMarker;
class CMarkerRenderable : public fwRenderable {
public:
	CMarkerRenderable(CMarker* data) {
		m_Data = data;
	}
	void Render() override;
private:
	CMarker* m_Data = nullptr;
};
#include "Project - The Framework/ExpandedExpressions/BoundedWhile.h"
struct sMarkerData {
	int Type = 1;
	CVector3 m_Position, m_Direction, m_Rotation, m_Scale;
	Color32 m_Color;
	bool m_DoesBounce = false, m_DoesFaceCam = false, DoesRotate = false, DoesInvert = false, Arg1 = false, Arg2 = false;
	int RotationOrder = 2;
	std::string m_Dictionary, m_TextureName;
};
class CMarker{
public:

	friend class CMarkerRenderable;
	CMarker() : m_Renderer(this) {}
	CMarker(const CMarker&) = delete;
	CMarker& operator=(const CMarker&) = delete;
	CMarker(CMarker&&) = delete;
	CMarker& operator=(CMarker&&) = delete;
	// ...
	sMarkerData& GetData() { return m_Data; }
	void SetTexture(std::string dictionary, std::string name);
	fwRenderable* GetRenderMtl() { return &this->m_Renderer; }
private:
	sMarkerData m_Data;
	CMarkerRenderable m_Renderer;
};