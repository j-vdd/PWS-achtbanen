#pragma once

#include "definitions/quat.h"

namespace math {

	typedef Quat<float> Quatf;
	typedef Quat<double> Quatd;


	template<typename T>
	Mat<3, 3, T> mat3_cast(const Quat<T>& q);

	template<typename T>
	Mat<4, 4, T> mat4_cast(const Quat<T>& q);

	template<typename T>
	Quat<T> quat_cast(const Mat<3, 3, T>& m);

	template<typename T>
	Quat<T> quat_cast(const Mat<4, 4, T>& m);

}

#include "definitions/func_quat.inl"