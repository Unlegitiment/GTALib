#pragma once
#include <ModCore/thirdparty/ScriptHook/include/types.h>
namespace legit {
	template<typename T, T SuitableDefault> class __Vector3 {
	public:
		using NewVec = __Vector3<T, SuitableDefault>;
		using Type = T;
		using OtherVec = __Vector3<T, SuitableDefault>;
		__Vector3() {
			this->x = SuitableDefault;
			this->y = SuitableDefault;
			this->z = SuitableDefault;
		}
		__Vector3(Vector3 Vector) {
			this->x = Vector.x;
			this->y = Vector.y;
			this->z = Vector.z;
		}
		__Vector3(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		NewVec Add(const OtherVec& other) {
			T x = this->x + other.x;
			T y = this->y + other.y;
			T z = this->z + other.z;
			return {x,y,};
		}
		NewVec Subtract(const OtherVec& other) {
			T x = this->x - other.x;
			T y = this->y - other.y;
			T z = this->z - other.z;
			return {x,y,z};
		}
		NewVec Scalef(float fScalar) {
			T x = this->x * fScalar;
			T y = this->y * fScalar;
			T z = this->z * fScalar;
			return {x,y,z};
		}
		NewVec ScaleV(const OtherVec& other) {
			T x = this->x * other.x;
			T y = this->y * other.y;
			T z = this->z * other.z;
			return {x,y,z};
		}
		Type Dot(const OtherVec& other) {
			Type value{};
			value += (this->x * other.x);
			value += (this->y * other.y);
			value += (this->z * other.z);
			return value;
		}
	public:
		Type x, y, z;
	};
	using Vec3f = __Vector3<float, 0.0f>;
	using Vec3i = __Vector3<int, 0>;
}