#pragma once

#include "types.h"
#include "mat3.h"
#include "mat4.h"

namespace math {

	template<typename T>
	struct Quat {

		typedef Quat<T> type;
		typedef T value_type;

		T s, x, y, z;

		static constexpr int length() { return 4; }

		constexpr T& operator[](int i);
		constexpr T const& operator[](int i) const;


		//constructors

		constexpr Quat() = default;
		constexpr Quat(const Quat& q) = default;
		

		//basic constructors

		constexpr Quat(T s, const Vec<3, T>& v);
		constexpr Quat(T s, T x, T y, T z);

		
		//conversion constructors

		template<typename U>
		constexpr Quat(const Quat<U>& q);

		template<typename A, typename B, typename C, typename D>
		constexpr Quat(A s, B x, C y, D z);

		Quat(const Vec<3, T>& u, const Vec<3, T>& v);

		explicit Quat(const Vec<3, T>& eulerAngle);
		explicit Quat(const Mat<3, 3, T>& m);
		explicit Quat(const Mat<4, 4, T>& m);

		
		//conversion operators

		explicit operator Mat<3, 3, T>() const;
		explicit operator Mat<4, 4, T>() const;


		//unary arithmetic operators

		Quat<T>& operator=(const Quat<T>& q) = default;

		template<typename U>
		Quat<T>& operator=(const Quat<U>& q);
		template<typename U>
		Quat<T>& operator+=(const Quat<U>& q);
		template<typename U>
		Quat<T>& operator-=(const Quat<U>& q);
		template<typename U>
		Quat<T>& operator*=(const Quat<U>& q);
		template<typename U>
		Quat<T>& operator*=(U s);
		template<typename U>
		Quat<T>& operator/=(U s);


	};


	//unary operators

	template<typename T>
	Quat<T> operator+(Quat<T> const& q);

	template<typename T>
	Quat<T> operator-(Quat<T> const& q);


	//binary operators

	template<typename T>
	Quat<T> operator+(Quat<T> const& p, Quat<T> const& q);

	template<typename T>
	Quat<T> operator-(Quat<T> const& p, Quat<T> const& q);

	template<typename T>
	Quat<T> operator*(Quat<T> const& p, Quat<T> const& q);


	template<typename T>
	Vec<3, T> operator*(Quat<T> const& q, Vec<3, T> const& v);

	template<typename T>
	Vec<3, T> operator*(Vec<3, T> const& v, Quat<T> const& q);


	template<typename T>
	Vec<4, T> operator*(Quat<T> const& q, Vec<4, T> const& v);

	template<typename T>
	Vec<4, T> operator*(Vec<4, T> const& v, Quat<T> const& q);


	template<typename T>
	Quat<T> operator*(Quat<T> const& q, T const& s);

	template<typename T>
	Quat<T> operator*(T const& s, Quat<T> const& q);

	template<typename T>
	Quat<T> operator/(Quat<T> const& q, T const& s);


	//boolean operators

	template<typename T>
	bool operator==(Quat<T> const& q1, Quat<T> const& q2);

	template<typename T>
	bool operator!=(Quat<T> const& q1, Quat<T> const& q2);

}

#include "quat.inl"