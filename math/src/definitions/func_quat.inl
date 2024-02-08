namespace math {

	template<typename T>
	Mat<3, 3, T> mat3_cast(Quat<T> const& q)
	{
		Mat<3, 3, T> Result(T(1));
		T qxx(q.x * q.x);
		T qyy(q.y * q.y);
		T qzz(q.z * q.z);
		T qxz(q.x * q.z);
		T qxy(q.x * q.y);
		T qyz(q.y * q.z);
		T qsx(q.s * q.x);
		T qsy(q.s * q.y);
		T qsz(q.s * q.z);

		Result[0][0] = T(1) - T(2) * (qyy + qzz);
		Result[0][1] = T(2) * (qxy + qsz);
		Result[0][2] = T(2) * (qxz - qsy);

		Result[1][0] = T(2) * (qxy - qsz);
		Result[1][1] = T(1) - T(2) * (qxx + qzz);
		Result[1][2] = T(2) * (qyz + qsx);

		Result[2][0] = T(2) * (qxz + qsy);
		Result[2][1] = T(2) * (qyz - qsx);
		Result[2][2] = T(1) - T(2) * (qxx + qyy);
		return Result;
	}

	template<typename T>
	Mat<4, 4, T> mat4_cast(Quat<T> const& q)
	{
		return Mat<4, 4, T>(mat3_cast(q));
	}

	template<typename T>
	Quat<T> quat_cast(Mat<3, 3, T> const& m)
	{
		/*T w = sqrt(1.0f + m[0][0] + m[1][1] + m[2][2]) / 2.0f;
		T w4 = 4.0f * w;
		return Quat<T>(
			w,
			-(m[2][1] - m[1][2]) / w4,
			-(m[0][2] - m[2][0]) / w4,
			-(m[1][0] - m[0][1]) / w4
		);*/

		T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
		T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
		T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
		T fourSSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

		int biggestIndex = 0;
		T fourBiggestSquaredMinus1 = fourSSquaredMinus1;
		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		T biggestVal = sqrt(fourBiggestSquaredMinus1 + static_cast<T>(1)) * static_cast<T>(0.5);
		T mult = static_cast<T>(0.25) / biggestVal;

		switch (biggestIndex)
		{
		case 0:
			return Quat<T>(biggestVal, (m[1][2] - m[2][1]) * mult, (m[2][0] - m[0][2]) * mult, (m[0][1] - m[1][0]) * mult);
		case 1:
			return Quat<T>((m[1][2] - m[2][1]) * mult, biggestVal, (m[0][1] + m[1][0]) * mult, (m[2][0] + m[0][2]) * mult);
		case 2:
			return Quat<T>((m[2][0] - m[0][2]) * mult, (m[0][1] + m[1][0]) * mult, biggestVal, (m[1][2] + m[2][1]) * mult);
		case 3:
			return Quat<T>((m[0][1] - m[1][0]) * mult, (m[2][0] + m[0][2]) * mult, (m[1][2] + m[2][1]) * mult, biggestVal);
		default: // Silence a -Wswitch-default warning in GCC. Should never actually get here. Assert is just for sanity.
			return Quat<T>(1, 0, 0, 0);
		}
	}

	template<typename T>
	Quat<T> quat_cast(Mat<4, 4, T> const& m)
	{
		return quat_cast(Mat<3, 3, T>(m));
	}

}