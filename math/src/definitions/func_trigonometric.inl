#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "_vectorize.h"

namespace math {

	template<int S, typename T>
	inline Vec<S, T> sin(const Vec<S, T>& v)
	{
		return Vectorize::Functor1<Vec, S, T, T>::call(std::sin, v);
	}

	template<int S, typename T>
	inline Vec<S, T> cos(const Vec<S, T>& v)
	{
		return Vectorize::Functor1<Vec, S, T, T>::call(std::cos, v);
	}

	template<int S, typename T>
	inline Vec<S, T> tan(const Vec<S, T>& v)
	{
		return Vectorize::Functor1<Vec, S, T, T>::call(std::tan, v);
	}

	template<typename T>
	inline Quat<T> quatRotor(const Vec<3, T> axis, T angle)
	{
		return Quat<T>(cos(angle), sin(angle) * axis);
	}

}