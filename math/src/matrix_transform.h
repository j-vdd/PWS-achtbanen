#pragma once

#include "definitions/types.h"

namespace math {

	template<typename T>
	Mat<4, 4, T> translate(const Mat<4, 4, T>& m, const Vec<3, T>& v);

	template<typename T>
	Mat<4, 4, T> rotate(const Mat<4, 4, T>& m, const Vec<3, T>& v, T angle);

	template<typename T>
	Mat<4, 4, T> scale(const Mat<4, 4, T>& m, const Vec<3, T>& v);

	template<typename T>
	Mat<4, 4, T> perspectiveTransform(T fov, T aspect, T near, T far);

	template<typename T>
	inline Mat<4, 4, T> modelTransform(const Vec<3, T>& position, const Vec<3, T>& rotation, float scale = 1.0f);
	template<typename T>
	inline Mat<4, 4, T> modelTransform(const Vec<3, T>& position, const Quat<T>& rotation, float scale = 1.0f);

	template<typename T>
	inline Mat<4, 4, T> inverseModelTransform(const Vec<3, T>& position, const Vec<3, T>& rotation, float scale = 1.0f);
	template<typename T>
	inline Mat<4, 4, T> inverseModelTransform(const Vec<3, T>& position, const Quat<T>& rotation, float scale = 1.0f);

	template<typename T>
	Mat<4, 4, T> viewTransform(const Vec<3, T>& position, const Vec<3, T>& rotation);
	template<typename T>
	inline Mat<4, 4, T> viewTransform(const Vec<3, T>& position, const Quat<T>& rotation);

}

#include "definitions/matrix_transform.inl"