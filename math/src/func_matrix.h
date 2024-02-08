#pragma once

#include "definitions/types.h"

namespace math {

	template<int C, int R, typename T>
	Mat<R, C, T> transpose(const Mat<C, R, T>& m);

	template<int C, typename T>
	T determinant(const Mat<C, C, T>& m);

	template<int C, typename T>
	Mat<C, C, T> inverse(const Mat<C, C, T>& m);

	template<int C, typename T>
	Mat<C, C, T> affineInverse(const Mat<C, C, T>& m);

	template<typename T>
	Mat<4, 4, T> orthonormalInverse(const Mat<4, 4, T>& m);

}

#include "definitions/func_matrix.inl"