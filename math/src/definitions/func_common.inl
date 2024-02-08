//TODO: types.h enough?
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "_vectorize.h"

namespace math {

	namespace Detail {

		template<typename T>
		inline constexpr T min(T a, T b) {
			return a < b ? a : b;
		}

		template<typename T>
		inline constexpr T max(T a, T b) {
			return a > b ? a : b;
		}

		template<typename T>
		inline constexpr T abs(T a) {
			return a < 0 ? -a : a;
		}

	}

	template<int S, typename T>
	inline constexpr Vec<S, T> abs(const Vec<S, T>& v) {
		return Vectorize::Functor1<Vec, S, T, T>::call(Detail::abs, v);
	}

	template<int S, typename T>
	inline constexpr Vec<S, T> min(const Vec<S, T>& v, T a) {
		return Vectorize::Functor2_vec_sca<Vec, S, T>::call(Detail::min, v, a);
	}

	template<int S, typename T>
	inline constexpr Vec<S, T> min(const Vec<S, T>& v1, const Vec<S, T>& v2) {
		return Vectorize::Functor2<Vec, S, T>::call(Detail::min, v1, v2);
	}

	template<int S, typename T>
	inline constexpr Vec<S, T> max(const Vec<S, T>& v, T a) {
		return Vectorize::Functor2_vec_sca<Vec, S, T>::call(Detail::max, v, a);
	}

	template<int S, typename T>
	inline constexpr Vec<S, T> max(const Vec<S, T>& v1, const Vec<S, T>& v2) {
		return Vectorize::Functor2<Vec, S, T>::call(Detail::max, v1, v2);
	}


	//rounding functions

	template<int S, typename T>
	inline constexpr Vec<S, T> floor(const Vec<S, T>& v) {
		return Vectorize::Functor1<Vec, S, T, T>::call(std::floor, v);
	}

	template<int S, typename T>
	inline constexpr Vec<S, T> ceil(const Vec<S, T>& v) {
		return Vectorize::Functor1<Vec, S, T, T>::call(std::ceil, v);
	}

	template<int S, typename T>
	inline constexpr Vec<S, T> round(const Vec<S, T>& v) {
		return Vectorize::Functor1<Vec, S, T, T>::call(std::round, v);
	}


	//mix

	template<int S, typename T, typename U>
	inline constexpr Vec<S, T> mix(const Vec<S, T>& v1, const Vec<S, T>& v2, U a) {
		return Vec<S, T>(Vec<S, U>(v1) * (static_cast<U>(1) - a) + Vec<S, U>(v2) * a);
	}

	template<int S, typename T, typename U>
	inline constexpr Vec<S, T> mix(const Vec<S, T>& v1, const Vec<S, T>& v2, const Vec<S, U>& a) {
		return Vec<S, T>(Vec<S, U>(v1) * (static_cast<U>(1) - a) + Vec<S, U>(v2) * a);
	}

	//clamp

	template<int S, typename T>
	inline constexpr Vec<S, T> clamp(const Vec<S, T>& v, T _min, T _max) {
		return max(min(v, _max), _min);
	}

}