#pragma once

#include "definitions/types.h"

namespace math {

	template<int S, typename T>
	constexpr Vec<S, T> abs(const Vec<S, T>& v);

	template<int S, typename T>
	constexpr Vec<S, T> min(const Vec<S, T>& v, T a);

	template<int S, typename T>
	constexpr Vec<S, T> min(const Vec<S, T>& v1, const Vec<S, T>& v2);

	template<int S, typename T>
	constexpr Vec<S, T> max(const Vec<S, T>& v1, T a);

	template<int S, typename T>
	constexpr Vec<S, T> max(const Vec<S, T>& v1, const Vec<S, T>& v2);


	//rounding functions

	template<int S, typename T>
	constexpr Vec<S, T> floor(const Vec<S, T>& v);

	template<int S, typename T>
	constexpr Vec<S, T> ceil(const Vec<S, T>& v);

	template<int S, typename T>
	constexpr Vec<S, T> round(const Vec<S, T>& v);

	
	//mix

	template<int S, typename T, typename U>
	constexpr Vec<S, T> mix(const Vec<S, T>& v1, const Vec<S, T>& v2, U a);

	template<int S, typename T, typename U>
	constexpr Vec<S, T> mix(const Vec<S, T>& v1, const Vec<S, T>& v2, const Vec<S, U>& a);


	//clamp

	template<int S, typename T>
	constexpr Vec<S, T> clamp(const Vec<S, T>& v, T min, T max);

}

#include "definitions/func_common.inl"