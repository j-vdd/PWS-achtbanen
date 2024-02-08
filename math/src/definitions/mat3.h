#pragma once

#include "types.h"
#include "vec3.h"

namespace math {

	template<typename T>
	struct Mat<3, 3, T>
	{

		typedef Vec<3, T> col_type;
		typedef Vec<3, T> row_type;
		typedef Mat<3, 3, T> type;
		typedef Mat<3, 3, T> transpose_type;
		typedef T value_type;

	private:
		col_type value[3];

	public:

		static constexpr int length() { return 3; }

		col_type& operator[](int i);
		constexpr col_type const& operator[](int i) const;


		//constructors

		constexpr Mat() = default;

		explicit constexpr Mat(const T& s);
		constexpr Mat(
			const T& x0, const T& y0, const T& z0,
			const T& x1, const T& y1, const T& z1,
			const T& x2, const T& y2, const T& z2
		);
		constexpr Mat(
			const col_type& v0,
			const col_type& v1,
			const col_type& v2
		);


		//conversion constructors

		template<
			typename X0, typename Y0, typename Z0,
			typename X1, typename Y1, typename Z1,
			typename X2, typename Y2, typename Z2
		>
		constexpr Mat(
			const X0& x0, const Y0& y0, const Z0& z0,
			const X1& x1, const Y1& y1, const Z1& z1,
			const X2& x2, const Y2& y2, const Z2& z2
		);

		template<typename V0, typename V1, typename V2>
		constexpr Mat(
			const Vec<3, V0>& v0,
			const Vec<3, V1>& v1,
			const Vec<3, V2>& v2
		);

		//matrix conversion constructors

		template<typename U>
		explicit constexpr Mat(const Mat<3, 3, U>& m);

		explicit constexpr Mat(const Mat<2, 2, T>& m);
		explicit constexpr Mat(const Mat<4, 4, T>& m);


		//unary arithmetic operators

		Mat<3, 3, T>& operator=(const Mat<3, 3, T>& m) = default;
		template<typename U>
		Mat<3, 3, T>& operator=(const Mat<3, 3, U>& m);

		template<typename U>
		Mat<3, 3, T>& operator+=(const Mat<3, 3, U>& m);
		template<typename U>
		Mat<3, 3, T>& operator+=(U s);

		template<typename U>
		Mat<3, 3, T>& operator-=(const Mat<3, 3, U>& m);
		template<typename U>
		Mat<3, 3, T>& operator-=(U s);

		template<typename U>
		Mat<3, 3, T>& operator*=(const Mat<3, 3, U>& m);
		template<typename U>
		Mat<3, 3, T>& operator*=(U s);

		template<typename U>
		Mat<3, 3, T>& operator/=(const Mat<3, 3, U>& m);
		template<typename U>
		Mat<3, 3, T>& operator/=(U s);


	};


	//unary operators

	template<typename T>
	Mat<3, 3, T> operator+(const Mat<3, 3, T>& m);

	template<typename T>
	Mat<3, 3, T> operator-(const Mat<3, 3, T>& m);


	//binary operators

	template<typename T>
	Mat<3, 3, T> operator+(const Mat<3, 3, T>& m1, const Mat<3, 3, T>& m2);

	template<typename T>
	Mat<3, 3, T> operator+(const Mat<3, 3, T>& m, T s);

	template<typename T>
	Mat<3, 3, T> operator+(T s, const Mat<3, 3, T>& m);

	template<typename T>
	Mat<3, 3, T> operator-(const Mat<3, 3, T>& m1, const Mat<3, 3, T>& m2);

	template<typename T>
	Mat<3, 3, T> operator-(const Mat<3, 3, T>& m, T s);

	template<typename T>
	Mat<3, 3, T> operator-(T s, const Mat<3, 3, T>& m);


	//multiplication

	template<typename T>
	Mat<3, 3, T> operator*(const Mat<3, 3, T>& m, T s);

	template<typename T>
	Mat<3, 3, T> operator*(T s, const Mat<3, 3, T>& m);

	template<typename T>
	typename Mat<3, 3, T>::col_type operator*(const Mat<3, 3, T>& m, const typename Mat<3, 3, T>::row_type& v);

	template<typename T>
	typename Mat<3, 3, T>::col_type operator*(const typename Mat<3, 3, T>::row_type& v, const Mat<3, 3, T>& m);

	template<typename T>
	Mat<3, 3, T> operator*(const Mat<3, 3, T>& m1, const Mat<3, 3, T>& m2);


	//division

	template<typename T>
	Mat<3, 3, T> operator/(const Mat<3, 3, T>& m, T s);

	template<typename T>
	Mat<3, 3, T> operator/(T s, const Mat<3, 3, T>& m);

	template<typename T>
	typename Mat<3, 3, T>::col_type operator/(const Mat<3, 3, T>& m, const typename Mat<3, 3, T>::row_type& v);

	template<typename T>
	typename Mat<3, 3, T>::col_type operator/(const typename Mat<3, 3, T>::row_type& v, const Mat<3, 3, T>& m);

	template<typename T>
	Mat<3, 3, T> operator/(const Mat<3, 3, T>& m1, const Mat<3, 3, T>& m2);


	//boolean operators

	template<typename T>
	bool operator==(const Mat<3, 3, T>& m1, const Mat<3, 3, T>& m2);

	template<typename T>
	bool operator!=(const Mat<3, 3, T>& m1, const Mat<3, 3, T>& m2);

}

#include "mat3.inl"