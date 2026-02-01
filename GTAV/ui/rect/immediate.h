#pragma once
#include <ModCore/math/Point.h>
#include <ModCore/math/Color.h>
#include <ModCore/math/Vector2.h>
#include <ModCore/thirdparty/ScriptHook/include/natives.h>
#include "rect_s.h"
#include <type_traits>
class CImRect : public sRect {
public:
	CImRect(legit::Pointf&& Center, legit::Vec2f&& Lengths, legit::Colorf&& Color, bool Unk = 1) {
		this->m_Center = std::move(Center);
		this->m_Side = std::move(Lengths);
		this->m_Color = std::move(Color);
		Draw(Unk);
	}
private:
	void Draw(bool unk) {
		GRAPHICS::DRAW_RECT(this->m_Center.x, this->m_Center.y, this->m_Side.x, this->m_Side.y, this->m_Color.r, this->m_Color.g, this->m_Color.b, this->m_Color.a, unk);
	}
public:
	CImRect() = default;
};