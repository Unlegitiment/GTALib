#include "Markers.h"
#include "../../../Project - The Game/SHV/natives.h"
void CMarkerRenderable::Render()
{
	if (m_Data == nullptr) renderLogf("Renderer has null owner");
	if (m_Data != (CMarker*)((char*)this - offsetof(CMarker, m_Renderer))) {
		renderLogf("Renderer owner pointer mismatch! this=%p, owner=%p, expected owner at %p",
			this, m_Data, (void*)((char*)this - offsetof(CMarker, m_Renderer)));
	}
	if (!m_Data->GetData().m_TextureName.empty() && m_Data->GetData().m_Dictionary.empty()) {
		renderLogf("Textures are broken Dict: %s, Name %s", m_Data->GetData().m_Dictionary.c_str(), m_Data->GetData().m_TextureName.c_str());
		m_Data->GetData().m_TextureName.clear();
	}
/*	renderLogf("Render call -> this=%p, m_Data=%p, dict='%s', tex='%s'",
		this, m_Data,
		m_Data ? m_Data->GetData().m_Dictionary.c_str() : "null",
		m_Data ? m_Data->GetData().m_TextureName.c_str() : "null"
	)*/;
	while(!m_Data->GetData().m_Dictionary.empty() && !GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(m_Data->GetData().m_Dictionary.c_str())) {
		renderLogf("Dictionary not loaded! Dictionary: %s, Texture Requested: %s", m_Data->GetData().m_Dictionary.c_str(), m_Data->GetData().m_TextureName.c_str());
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(m_Data->GetData().m_Dictionary.c_str(), 1);
		WAIT(0);
	}// "mpmissmarkers256", "custom_icon"
	GRAPHICS::DRAW_MARKER_EX(this->m_Data->GetData().Type, 
		this->m_Data->GetData().m_Position.GetX(), this->m_Data->GetData().m_Position.GetY(), this->m_Data->GetData().m_Position.GetZ(), 
		m_Data->GetData().m_Direction.GetX(), m_Data->GetData().m_Direction.GetY(), m_Data->GetData().m_Direction.GetZ(),
		m_Data->GetData().m_Rotation.GetX(), m_Data->GetData().m_Rotation.GetY(), m_Data->GetData().m_Rotation.GetZ(),
		m_Data->GetData().m_Scale.GetX(), m_Data->GetData().m_Scale.GetY(), m_Data->GetData().m_Scale.GetZ(),
		m_Data->GetData().m_Color.GetR(), m_Data->GetData().m_Color.GetG(), m_Data->GetData().m_Color.GetB(), m_Data->GetData().m_Color.GetA(),
		m_Data->GetData().m_DoesBounce, m_Data->GetData().m_DoesFaceCam, m_Data->GetData().RotationOrder, m_Data->GetData().DoesRotate, 
		m_Data->GetData().m_Dictionary.empty() ? NULL : m_Data->GetData().m_Dictionary.c_str(),
		m_Data->GetData().m_TextureName.empty() ? NULL : m_Data->GetData().m_TextureName.c_str(),
		m_Data->GetData().DoesInvert, m_Data->GetData().Arg1, m_Data->GetData().Arg2
	);
}

void CMarker::SetTexture(std::string dictionary, std::string name) {
	if ((m_Data.Type != 8 && m_Data.Type != 9) && (!dictionary.empty() || !name.empty())) {
		renderLogf("This Type of Marker does not really support a Texture. This will look weird.");
	}
	this->m_Data.m_Dictionary = dictionary;
	this->m_Data.m_TextureName = name;
	static constexpr int MAX_ATT = 10;
	auto res = BoundedWhile([&]()->bool {return !GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(m_Data.m_Dictionary.c_str()); }, MAX_ATT, [&](bool cond, int att)->void {
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(m_Data.m_Dictionary.c_str(), 1);
			renderLogf(__FUNCTION__"Bounded while ran, %s", m_Data.m_Dictionary.c_str());
			WAIT(0);
		});
	
}
