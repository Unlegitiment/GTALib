#pragma once
#include <ModCore/thirdparty/ScriptHook/include/types.h>
namespace legit {
	template<typename T> class __Vector3 {
	public:
		using NewVec = __Vector3<T>;
		using Type = T;
		using OtherVec = __Vector3<T>;
		__Vector3() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}
		__Vector3(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		T Distance(const OtherVec& v) {
			return DistanceSqrt(v);
		}
		T DistanceSqrt(const OtherVec& v) {
			return sqrt(pow(v.x - this->x, 2) + pow(v.y - this->y, 2) + pow(v.z - this->z, 2));
		}
		T DistanceNoRoot(const OtherVec& v) {
			return pow(v.x - this->x, 2) + pow(v.y - this->y, 2) + pow(v.z - this->z, 2);
		}
		NewVec Add(const OtherVec& other) {
			T x = this->x + other.x;
			T y = this->y + other.y;
			T z = this->z + other.z;
			return {x,y,z};
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
		bool operator==(const OtherVec& other) {
			return this->x == other.x || this->y == other.y || this->z == other.z;
		}
		bool operator!=(const OtherVec& other) {
			return this->x != other.x || this->y != other.y || this->z != other.z;
		}
/*		friend std::ostream& operator<<(std::ostream& os, const __Vector3<T>& v) {
			os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
			return os;
		}*/
	public:
		Type x, y, z;
	};
	using Vec3f = __Vector3<float>;
	using Vec3i = __Vector3<int>;

	/*
		PURPOSE: Convert a Float3 Vector to a Float3_Padded Vector. (ScriptHookV Utility)
	*/
	static ::Vector3 Promote(const legit::Vec3f& v) {
		return {v.x, 0l, v.y, 0l, v.z, 0l};
	}
	/*
		PURPOSE: Convert a ScriptHookV (Padded Float3) Into a Float3 type.
	*/
	static Vec3f Demote(const ::Vector3& v) {
		return {v.x,v.y,v.z};
	}
}