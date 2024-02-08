#pragma once

#include "types.h"

namespace math {

	template<typename T>
	struct Vec<3, T> {

		union { T x, r;};
		union { T y, g;};
		union { T z, b;};

		static constexpr int size() {
			return 3;
		}

		constexpr T& operator[](int i);
		constexpr T const& operator[](int i) const;

		//constructors

		Vec() = default;
		Vec(const Vec& v) = default;

		Vec(T x, T y, T z);
		explicit Vec(T scalar);

		//conversion constructors

		template<typename A, typename B, typename C>
		Vec(A x, B y, C z);

		//conversion vector constructors

		template<typename U>
		explicit Vec(const Vec<3, U>& v);
		template<typename U>
		explicit Vec(const Vec<4, U>& v);
		template<typename U>
		explicit Vec(const Vec<2, U>& _xy, U _z);
		template<typename U>
		explicit Vec(U _x, const Vec<2, U>& _yz);


		//unary arithmetic operators

		Vec& operator=(const Vec& v) = default;

		template<typename U>
		Vec& operator=(const Vec<3, U>& v);

		template<typename U>
		Vec<3, T>& operator+=(const Vec<3, U>& v);
		template<typename U>
		Vec<3, T>& operator+=(U scalar);
		template<typename U>
		Vec<3, T>& operator-=(const Vec<3, U>& v);
		template<typename U>
		Vec<3, T>& operator-=(U scalar);
		template<typename U>
		Vec<3, T>& operator*=(const Vec<3, U>& v);
		template<typename U>
		Vec<3, T>& operator*=(U scalar);
		template<typename U>
		Vec<3, T>& operator/=(const Vec<3, U>& v);
		template<typename U>
		Vec<3, T>& operator/=(U scalar);

		//increment and decrement operators

		Vec<3, T>& operator++();
		Vec<3, T>& operator--();


	};

	//unary operators

	template<typename T>
	Vec<3, T> operator+(const Vec<3, T>& v);

	template<typename T>
	Vec<3, T> operator-(const Vec<3, T>& v);


	//binary operators

	template<typename T>
	Vec<3, T> operator+(const Vec<3, T>& v1, const Vec<3, T>& v2);
	template<typename T>
	Vec<3, T> operator+(const Vec<3, T>& v, T scalar);
	template<typename T>
	Vec<3, T> operator+(T scalar, const Vec<3, T>& v);

	template<typename T>
	Vec<3, T> operator-(const Vec<3, T>& v1, const Vec<3, T>& v2);
	template<typename T>
	Vec<3, T> operator-(const Vec<3, T>& v, T scalar);
	template<typename T>
	Vec<3, T> operator-(T scalar, const Vec<3, T>& v);

	template<typename T>
	Vec<3, T> operator*(const Vec<3, T>& v1, const Vec<3, T>& v2);
	template<typename T>
	Vec<3, T> operator*(const Vec<3, T>& v, T scalar);
	template<typename T>
	Vec<3, T> operator*(T scalar, const Vec<3, T>& v);

	template<typename T>
	Vec<3, T> operator/(const Vec<3, T>& v1, const Vec<3, T>& v2);
	template<typename T>
	Vec<3, T> operator/(const Vec<3, T>& v, T scalar);
	template<typename T>
	Vec<3, T> operator/(T scalar, const Vec<3, T>& v);

	//boolean operators

	template<typename T>
	bool operator==(const Vec<3, T>& v1, const Vec<3, T>& v2);

	template<typename T>
	bool operator!=(const Vec<3, T>& v1, const Vec<3, T>& v2);

	//returns true if all components are greater
	template<typename T>
	bool operator>(const Vec<3, T>& v1, const Vec<3, T>& v2);

	//returns true if all components are greater or equal
	template<typename T>
	bool operator>=(const Vec<3, T>& v1, const Vec<3, T>& v2);

	//returns true if all components are smaller
	template<typename T>
	bool operator<(const Vec<3, T>& v1, const Vec<3, T>& v2);

	//returns true if all components are smaller or equal
	template<typename T>
	bool operator<=(const Vec<3, T>& v1, const Vec<3, T>& v2);

}

#include "vec3.inl"