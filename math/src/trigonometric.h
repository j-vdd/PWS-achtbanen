#pragma once

#include "definitions/types.h"

namespace math {

	template<int S, typename T>
	Vec<S, T> sin(const Vec<S, T>& v);

	template<int S, typename T>
	Vec<S, T> cos(const Vec<S, T>& v);

	template<int S, typename T>
	Vec<S, T> tan(const Vec<S, T>& v);

	template<typename T>
	Quat<T> quatRotor(const Vec<3, T> axis, T angle);

}

#include "definitions/func_trigonometric.inl"