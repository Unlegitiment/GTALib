#pragma once
namespace legit {
	template<typename T, int SuitableDefault> class __Vector2 {
	public:
		using NewVec = __Vector2<T, SuitableDefault>;
		using Type = T;
		using OtherVec = __Vector2<T, SuitableDefault>;

		__Vector2() {
			this->x = SuitableDefault;
			this->y = SuitableDefault;
		}
		__Vector2(T x, T y) {
			this->x = x;
			this->y = y;
		}
		NewVec Add(const OtherVec& other) {
			T x = this->x + other.x;
			T y = this->y + other.y;
			return {x,y};
		}
		NewVec Subtract(const OtherVec& other) {
			T x = this->x - other.x;
			T y = this->y - other.y;
			return {x,y};
		}
		NewVec Scalef(float fScalar) {
			T x = this->x * fScalar;
			T y = this->y * fScalar;
			return {x,y};
		}
		NewVec ScaleV(const OtherVec& other) {
			T x = this->x * other.x;
			T y = this->y * other.y;
			return {x,y};
		}
		Type Dot(const OtherVec& other) {
			Type value{};
			value += (this->x * other.x);
			value += (this->y * other.y);
			return value;
		}
		Type Distance(const OtherVec& v) {
			return DistanceSqrt(v);
		}
		Type DistanceSqrt(const OtherVec& v) {
			return sqrt(pow(v.x - this->x, 2) + pow(v.y - this->y, 2));
		}
		Type DistanceNoRoot(const OtherVec& v) {
			return pow(v.x - this->x, 2) + pow(v.y - this->y, 2);
		}
	public:
		Type x, y;
	};
	using Vec2f = __Vector2<float, 0>;
	using Vec2i = __Vector2<int, 0>;

}