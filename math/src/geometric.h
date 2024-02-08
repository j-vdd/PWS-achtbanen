#pragma once

#include "definitions/types.h"

namespace math {

	//dot, cross, length, normalize

	template<int S, typename T>
	constexpr T dot(const Vec<S, T>& v1, const Vec<S, T>& v2);
	template<typename T>
	constexpr T dot(const Quat<T>& q1, const Quat<T>& q2);

	template<typename T>
	constexpr Vec<3, T> cross(const Vec<3, T>& v1, const Vec<3, T>& v2);
	template<typename T>
	constexpr Quat<T> cross(const Quat<T>& q1, const Quat<T>& q2);

	template<int S, typename T>
	constexpr T length(const Vec<S, T>& v);
	template<typename T>
	constexpr T length(const Quat<T>& q);

	template<int S, typename T>
	constexpr Vec<S, T> normalize(const Vec<S, T>& v);
	template<typename T>
	constexpr Quat<T> normalize(const Quat<T>& q);

	template<typename T>
	constexpr Quat<T> conjugate(const Quat<T>& q);

	template<typename T>
	Quat<T> quatRotor(const Vec<3, T> axis, T angle);

	template<typename T>
	constexpr Vec<3, T> quatRotate(const Quat<T>& rotor, const Vec<3, T>& v);
	template<typename T>
	constexpr Vec<4, T> quatRotate(const Quat<T>& rotor, const Vec<4, T>& v);

	template<typename T>
	constexpr Quat<T> inverse(const Quat<T>& q);

	//template<typename T>
	//constexpr Quat<T> unitQuat(const Quat<T>& q);

}

#include "definitions/func_geometric.inl"