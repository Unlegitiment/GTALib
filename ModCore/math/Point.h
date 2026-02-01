#pragma once
namespace legit{
	template<typename T, int SuitableDefault>
	class Point {
	public:
		using NewPt = Point<T, SuitableDefault>;
		using OtherPt = Point<T, SuitableDefault>;
		Point() {
			x = SuitableDefault;
			y = SuitableDefault;
		}
		Point(T x, T y) {
			this->x = x;
			this->y = y;
		}
		NewPt Add(const OtherPt& other) {
			return {this->x + other.x, this->y + other.y};
		}
		NewPt Subtract(const OtherPt& other) {
			return {this->x - other.x, this->y - other.y};
		}
		NewPt Multiply(const OtherPt& other) {
			return {this->x * other.x, this->y * other.y};
		}
		NewPt Divide(const OtherPt& other) {
			return {this->x / other.x, this->y / other.y};
		}
	public:
		T x, y;
	};
	using Pointf = Point<float, 0>;
	using Pointd = Point<int, 0>;


}