#pragma once
namespace rage {
	template<typename T>
	static void Clamp(T& Value, const T& Minimum, const T& Maximum) {
		if (Value > Maximum) Value = Maximum;
		if (Value < Minimum) Value = Minimum;
	}
}