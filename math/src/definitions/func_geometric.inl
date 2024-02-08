#include "_vectorize.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "quat.h"

namespace math {

	template<typename T>
	inline constexpr T dot(const Vec<2, T>& v1, const Vec<2, T>& v2) 
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
	template<typename T>
	inline constexpr T dot(const Vec<3, T>& v1, const Vec<3, T>& v2) 
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	template<typename T>
	inline constexpr T dot(const Vec<4, T>& v1, const Vec<4, T>& v2) 
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}
	/*template<int S, typename T>
	inline constexpr T dot(const Vec<S, T>& v1, const Vec<S, T>& v2)
	{
		T sum = static_cast<T>(0);
		for (int i = 0; i < S; i++) {
			sum += v1[i] * v2[i];
		}

		return sum;
	}*/
	template<typename T>
	inline constexpr T dot(const Quat<T>& q1, const Quat<T>& q2) 
	{
		return q1.s * q2.s + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	}

	template<typename T>
	inline constexpr Vec<3, T> cross(const Vec<3, T>& v1, const Vec<3, T>& v2) 
	{
		return Vec<3, T>(
			v1.y * v2.z - v2.y * v1.z,
			v1.z * v2.x - v2.z * v1.x,
			v1.x * v2.y - v2.x * v1.y
		);
	}
	template<typename T>
	inline constexpr Quat<T> cross(const Quat<T>& q1, const Quat<T>& q2) {
		return Quat<T>(
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
			q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x
		);
	}

	template<int S, typename T>
	inline constexpr T length(const Vec<S, T>& v)
	{
		return sqrt(dot(v, v));
	}
	template<typename T>
	inline constexpr T length(const Quat<T>& q) 
	{
		return sqrt(dot(q, q));
	}

	template<int S, typename T>
	inline constexpr Vec<S, T> normalize(const Vec<S, T>& v) 
	{
		return v * (T(1) / length(v));
	}
	template<typename T>
	inline constexpr Quat<T> normalize(const Quat<T>& q)
	{
		return q * (T(1) / length(q));
	}

	template<typename T>
	inline constexpr Quat<T> conjugate(const Quat<T>& q)
	{
		return Quat<T>(q.s, -q.x, -q.y, -q.z);
	}

	template<typename T>
	inline constexpr Vec<3, T> quatRotate(const Quat<T>& rotor, const Vec<3, T>& v)
	{
		constexpr Quat<T> quat = rotor * Quat<T>(0, v) * conjugate(rotor);
		return Vec<3, T>(quat.x, quat.y, quat.z);
	}
	template<typename T>
	inline constexpr Vec<4, T> quatRotate(const Quat<T>& rotor, const Vec<4, T>& v)
	{
		constexpr Quat<T> quat = rotor * Quat<T>(0, v.x, v.y, v.z) * conjugate(rotor);
		return Vec<4, T>(quat.x, quat.y, quat.z, v.w);
	}

	template<typename T>
	inline constexpr Quat<T> inverse(const Quat<T>& q)
	{
		return conjugate(q) / dot(q, q);
	}

	//template<typename T>
	//inline constexpr Quat<T> unitQuat(const Quat<T>& q)
	//{
	//	return Quat<T>(static_cast<T>(0), normalize(q.v));
	//}

}