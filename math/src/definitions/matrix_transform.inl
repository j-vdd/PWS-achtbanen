#include "mat4.h"
#include "vec3.h"
#include "quat.h"

#include "../geometric.h"

namespace math {

	template<typename T>
	inline Mat<4, 4, T> translate(const Mat<4, 4, T>& m, const Vec<3, T>& v) {
		Mat<4, 4, T> Result(m);
		Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return Result;
	}

	template<typename T>
	inline Mat<4, 4, T> rotate(const Mat<4, 4, T>& m, const Vec<3, T>& v, T angle) {
		T const a = angle;
		T const c = std::cos(a);
		T const s = std::sin(a);

		Vec<3, T> axis(normalize(v));
		Vec<3, T> temp((T(1) - c) * axis);

		Mat<4, 4, T> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		Mat<4, 4, T> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	inline Mat<4, 4, T> scale(const Mat<4, 4, T>& m, const Vec<3, T>& v) {
		Mat<4, 4, T> Result;

		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];

		return Result;
	}

	template<typename T>
	inline Mat<4, 4, T> perspectiveTransform(T fov, T aspect, T near, T far)
	{
		const T s = static_cast<T>(1) / std::tan(fov * static_cast<T>(0.5f));

		return Mat<4, 4, T>(
			s / aspect, 0, 0, 0,
			0, s, 0, 0,
			0, 0, -(near + far) / (far - near), -1,
			0, 0, -2 * near * far / (far - near), 0
		);
	}

	template<typename T>
	inline Mat<4, 4, T> modelTransform(const Vec<3, T>& position, const Vec<3, T>& rotation, float scalation)
	{
		Mat<4, 4, T> Identity(1);

		return
			translate(Identity, position) *
			rotate(Identity, { 0, 1, 0 }, rotation.y) *
			rotate(Identity, { 1, 0, 0 }, rotation.x) *
			rotate(Identity, { 0, 0, 1 }, rotation.z) *
			scale(Identity, Vec3( scalation ));
	}
	template<typename T>
	inline Mat<4, 4, T> modelTransform(const Vec<3, T>& position, const Quat<T>& rotation, float scalation)
	{
		Mat<4, 4, T> Identity(1);

		return translate(Identity, position) * mat4_cast(rotation) * scale(Identity, Vec3(scalation));
	}

	template<typename T>
	inline Mat<4, 4, T> inverseModelTransform(const Vec<3, T>& position, const Vec<3, T>& rotation, float scalation)
	{
		Mat<4, 4, T> Identity(1);

		return
			scale(Identity, Vec3(1.0f / scalation)) *
			rotate(Identity, { 0, 1, 0 }, -rotation.z) *
			rotate(Identity, { 1, 0, 0 }, -rotation.x) *
			rotate(Identity, { 0, 0, 1 }, -rotation.y) *
			translate(Identity, -position);
	}
	template<typename T>
	inline Mat<4, 4, T> inverseModelTransform(const Vec<3, T>& position, const Quat<T>& rotation, float scalation)
	{
		Mat<4, 4, T> Identity(1);

		return scale(Identity, Vec3(1.0f / scalation)) * mat4_cast(-rotation) * translate(Identity, -position);
	}

	template<typename T>
	inline Mat<4, 4, T> viewTransform(const Vec<3, T>& position, const Vec<3, T>& rotation)
	{
		Mat<4, 4, T> Identity(1);

		return 
			rotate(Identity, {0, 0, 1}, -rotation.z) *
			rotate(Identity, {1, 0, 0}, -rotation.x) *
			rotate(Identity, {0, 1, 0}, -rotation.y) *
			translate(Identity, -position);
	}
	template<typename T>
	inline Mat<4, 4, T> viewTransform(const Vec<3, T>& position, const Quat<T>& rotation)
	{
		Mat<4, 4, T> Identity(1);

		return mat4_cast(Quat<T>(-rotation.s, rotation.x, rotation.y, rotation.z)) * translate(Identity, -position); //TODO: does -rotation work? (or use conjugate)
	}

}