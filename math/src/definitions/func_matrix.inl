#include "mat2.h"
#include "mat3.h"
#include "mat4.h"

namespace math {


	template<typename T>
	inline Mat<2, 2, T> transpose(const Mat<2, 2, T>& m) {
		Mat<2, 2, T> result;

		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		
		return result;
	}

	template<typename T>
	inline Mat<3, 3, T> transpose(const Mat<3, 3, T>& m) {
		Mat<3, 3, T> result;

		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		
		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		
		return result;
	}

	template<typename T>
	inline Mat<4, 4, T> transpose(const Mat<4, 4, T>& m) {
		Mat<4, 4, T> result;

		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[0][3] = m[3][0];
		
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		result[1][3] = m[3][1];
		
		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		result[2][3] = m[3][2];
		
		result[3][0] = m[0][3];
		result[3][1] = m[1][3];
		result[3][2] = m[2][3];
		result[3][3] = m[3][3];

		return result;
	}

	template<typename T>
	inline T determinant(const Mat<2, 2, T>& m) {
		return m[0][0] * m[1][1] - m[1][0] * m[0][1];
	}

	template<typename T>
	inline T determinant(const Mat<3, 3, T>& m) {
		return
			+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
			- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
			+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
	}

	template<typename T>
	inline T determinant(const Mat<4, 4, T>& m) {
		T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

		Vec<4, T> DetCof(
			+(m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02),
			-(m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04),
			+(m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05),
			-(m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05));

		return
			m[0][0] * DetCof[0] + m[0][1] * DetCof[1] +
			m[0][2] * DetCof[2] + m[0][3] * DetCof[3];
	}

	template<typename T>
	inline Mat<2, 2, T> inverse(const Mat<2, 2, T>& m) {
		T OneOverDeterminant = static_cast<T>(1) / (
			+m[0][0] * m[1][1]
			- m[1][0] * m[0][1]);

		Mat<2, 2, T> Inverse(
			+m[1][1] * OneOverDeterminant,
			-m[0][1] * OneOverDeterminant,
			-m[1][0] * OneOverDeterminant,
			+m[0][0] * OneOverDeterminant);

		return Inverse;
	}

	template<typename T>
	inline Mat<3, 3, T> inverse(const Mat<3, 3, T>& m) {
		T OneOverDeterminant = static_cast<T>(1) / (
			+m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
			- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
			+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

		Mat<3, 3, T> Inverse;
		Inverse[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * OneOverDeterminant;
		Inverse[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * OneOverDeterminant;
		Inverse[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * OneOverDeterminant;
		Inverse[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * OneOverDeterminant;
		Inverse[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * OneOverDeterminant;
		Inverse[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * OneOverDeterminant;
		Inverse[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * OneOverDeterminant;
		Inverse[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * OneOverDeterminant;
		Inverse[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * OneOverDeterminant;

		return Inverse;
	}

	template<typename T>
	inline Mat<4, 4, T> inverse(const Mat<4, 4, T>& m) {
		T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		Vec<4, T> Fac0(Coef00, Coef00, Coef02, Coef03);
		Vec<4, T> Fac1(Coef04, Coef04, Coef06, Coef07);
		Vec<4, T> Fac2(Coef08, Coef08, Coef10, Coef11);
		Vec<4, T> Fac3(Coef12, Coef12, Coef14, Coef15);
		Vec<4, T> Fac4(Coef16, Coef16, Coef18, Coef19);
		Vec<4, T> Fac5(Coef20, Coef20, Coef22, Coef23);

		Vec<4, T> _Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		Vec<4, T> _Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		Vec<4, T> _Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		Vec<4, T> _Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		Vec<4, T> Inv0(_Vec1 * Fac0 - _Vec2 * Fac1 + _Vec3 * Fac2);
		Vec<4, T> Inv1(_Vec0 * Fac0 - _Vec2 * Fac3 + _Vec3 * Fac4);
		Vec<4, T> Inv2(_Vec0 * Fac1 - _Vec1 * Fac3 + _Vec3 * Fac5);
		Vec<4, T> Inv3(_Vec0 * Fac2 - _Vec1 * Fac4 + _Vec2 * Fac5);

		Vec<4, T> SignA(+1, -1, +1, -1);
		Vec<4, T> SignB(-1, +1, -1, +1);
		Mat<4, 4, T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		Vec<4, T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		Vec<4, T> Dot0(m[0] * Row0);
		T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		T OneOverDeterminant = static_cast<T>(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}

	template<typename T>
	inline Mat<3, 3, T> affineInverse(const Mat<3, 3, T>& m) {
		const Mat<2, 2, T> Inv(inverse(Mat<2, 2, T>(m)));

		return Mat<3, 3, T>(
			Vec<3, T>(Inv[0], static_cast<T>(0)),
			Vec<3, T>(Inv[1], static_cast<T>(0)),
			Vec<3, T>(-Inv * Vec<2, T>(m[2]), static_cast<T>(1))
		);
	}

	template<typename T>
	inline Mat<4, 4, T> affineInverse(const Mat<4, 4, T>& m) {
		const Mat<3, 3, T> Inv(inverse(Mat<3, 3, T>(m)));

		return Mat<4, 4, T>(
			Vec<4, T>(Inv[0], static_cast<T>(0)),
			Vec<4, T>(Inv[1], static_cast<T>(0)),
			Vec<4, T>(Inv[2], static_cast<T>(0)),
			Vec<4, T>(-Inv * Vec<3, T>(m[3]), static_cast<T>(1))
		);
	}

	template<typename T>
	inline Mat<4, 4, T> orthonormalInverse(const Mat<4, 4, T>& m) {
		const Mat<3, 3, T> Inv(transpose(Mat<3, 3, T>(m)));

		return Mat<4, 4, T>(
			Vec<4, T>(Inv[0], static_cast<T>(0)),
			Vec<4, T>(Inv[1], static_cast<T>(0)),
			Vec<4, T>(Inv[2], static_cast<T>(0)),
			Vec<4, T>(-Inv * Vec<3, T>(m[3]), static_cast<T>(1))
		);
	}

}