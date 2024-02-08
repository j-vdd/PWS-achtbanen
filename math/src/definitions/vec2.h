#pragma once

#include "types.h"

namespace math {

	template<typename T>
	struct Vec<2, T> {

		union { T x, r; };
		union { T y, g; };

		static constexpr int size() {
			return 2;
		}

		constexpr T& operator[](int i);
		constexpr T const& operator[](int i) const;
		
		//constructors

		Vec() = default;
		Vec(const Vec& v) = default;

		Vec(T x, T y);
		explicit Vec(T scalar);

		//conversion constructors

		template<typename A, typename B>
		Vec(A x, B y);

		//conversion vector constructors

		template<typename U>
		explicit Vec(const Vec<2, U>& v);
		template<typename U>
		explicit Vec(const Vec<3, U>& v);
		template<typename U>
		explicit Vec(const Vec<4, U>& v);


		//unary arithmetic operators

		Vec& operator=(const Vec& v) = default;

		template<typename U>
		Vec& operator=(const Vec<2, U>& v);

		template<typename U>
		Vec<2, T>& operator+=(const Vec<2, U>& v);
		template<typename U>
		Vec<2, T>& operator+=(U scalar);
		template<typename U>
		Vec<2, T>& operator-=(const Vec<2, U>& v);
		template<typename U>
		Vec<2, T>& operator-=(U scalar);
		template<typename U>
		Vec<2, T>& operator*=(const Vec<2, U>& v);
		template<typename U>
		Vec<2, T>& operator*=(U scalar);
		template<typename U>
		Vec<2, T>& operator/=(const Vec<2, U>& v);
		template<typename U>
		Vec<2, T>& operator/=(U scalar);

		//increment and decrement operators

		Vec<2, T>& operator++();
		Vec<2, T>& operator--();

		
	};

	//unary operators

	template<typename T>
	Vec<2, T> operator+(const Vec<2, T>& v);

	template<typename T>
	Vec<2, T> operator-(const Vec<2, T>& v);

	
	//binary operators

	template<typename T>
	Vec<2, T> operator+(const Vec<2, T>& v1, const Vec<2, T>& v2);
	template<typename T>
	Vec<2, T> operator+(const Vec<2, T>& v, T scalar);
	template<typename T>
	Vec<2, T> operator+(T scalar, const Vec<2, T>& v);

	template<typename T>
	Vec<2, T> operator-(const Vec<2, T>& v1, const Vec<2, T>& v2);
	template<typename T>
	Vec<2, T> operator-(const Vec<2, T>& v, T scalar);
	template<typename T>
	Vec<2, T> operator-(T scalar, const Vec<2, T>& v);

	template<typename T>
	Vec<2, T> operator*(const Vec<2, T>& v1, const Vec<2, T>& v2);
	template<typename T>
	Vec<2, T> operator*(const Vec<2, T>& v, T scalar);
	template<typename T>
	Vec<2, T> operator*(T scalar, const Vec<2, T>& v);

	template<typename T>
	Vec<2, T> operator/(const Vec<2, T>& v1, const Vec<2, T>& v2);
	template<typename T>
	Vec<2, T> operator/(const Vec<2, T>& v, T scalar);
	template<typename T>
	Vec<2, T> operator/(T scalar, const Vec<2, T>& v);

	//boolean operators

	template<typename T>
	bool operator==(const Vec<2, T>& v1, const Vec<2, T>& v2);

	template<typename T>
	bool operator!=(const Vec<2, T>& v1, const Vec<2, T>& v2);

	//returns true if all components are greater
	template<typename T>
	bool operator>(const Vec<2, T>& v1, const Vec<2, T>& v2);

	//returns true if all components are greater or equal
	template<typename T>
	bool operator>=(const Vec<2, T>& v1, const Vec<2, T>& v2);

	//returns true if all components are smaller
	template<typename T>
	bool operator<(const Vec<2, T>& v1, const Vec<2, T>& v2);

	//returns true if all components are smaller or equal
	template<typename T>
	bool operator<=(const Vec<2, T>& v1, const Vec<2, T>& v2);

}

#include "vec2.inl"