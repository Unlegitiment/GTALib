#pragma once
namespace legit {
	template<typename T>
	class Color {
	public:
		Color() = default;
		Color(T _r, T _g, T _b, T _a) : r(_r), g(_g), b(_b), a(_a){

		}
		template<typename R> Color(const Color<R>& Other) {
			this->r = (T)Other.r;
			this->g = (T)Other.g;
			this->b = (T)Other.b;
			this->a = (T)Other.a;
		}
	public:
		T r = 0, g= 0, b= 0, a = 0;

	};
	using Colorf = Color<float>;
}