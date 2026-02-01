#pragma once
namespace legit {
	template<typename T>
	class Color {
	public:
		Color() = default;
		Color(T _r, T _g, T _b, T _a) : r(_r), g(_g), b(_b), a(_a){

		}
	public:
		T r = 0, g= 0, b= 0, a = 0;

	};
	using Colorf = Color<float>;
}