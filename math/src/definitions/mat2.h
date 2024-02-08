#pragma once

#include "types.h"
#include "vec2.h"

namespace math {

	template<typename T>
	struct Mat<2, 2, T>
	{

		typedef Vec<2, T> col_type;
		typedef Vec<2, T> row_type;
		typedef Mat<2, 2, T> type;
		typedef Mat<2, 2, T> transpose_type;
		typedef T value_type;

	private:
		col_type value[2];

	public:

		static constexpr int length() { return 2; }

		col_type& operator[](int i);
		constexpr col_type const& operator[](int i) const;


		//constructors

		constexpr Mat() = default;

		explicit constexpr Mat(const T& s);
		constexpr Mat(
			const T& x0, const T& y0,
			const T& x1, const T& y1
		);
		constexpr Mat(
			const col_type& v0,
			const col_type& v1
		);


		//conversion constructors

		template<
			typename X0, typename Y0,
			typename X1, typename Y1
		>
		constexpr Mat(
			const X0& x0, const Y0& y0,
			const X1& x1, const Y1& y1
		);

		template<typename V0, typename V1>
		constexpr Mat(
			const Vec<2, V0>& v0,
			const Vec<2, V1>& v1
		);

		//matrix conversion constructors

		template<typename U>
		explicit constexpr Mat(const Mat<2, 2, U>& m);

		explicit constexpr Mat(const Mat<3, 3, T>& m);
		explicit constexpr Mat(const Mat<4, 4, T>& m);


		//unary arithmetic operators

		Mat<2, 2, T>& operator=(const Mat<2, 2, T>& m) = default;
		template<typename U>
		Mat<2, 2, T>& operator=(const Mat<2, 2, U>& m);

		template<typename U>
		Mat<2, 2, T>& operator+=(const Mat<2, 2, U>& m);
		template<typename U>
		Mat<2, 2, T>& operator+=(U s);

		template<typename U>
		Mat<2, 2, T>& operator-=(const Mat<2, 2, U>& m);
		template<typename U>
		Mat<2, 2, T>& operator-=(U s);

		template<typename U>
		Mat<2, 2, T>& operator*=(const Mat<2, 2, U>& m);
		template<typename U>
		Mat<2, 2, T>& operator*=(U s);

		template<typename U>
		Mat<2, 2, T>& operator/=(const Mat<2, 2, U>& m);
		template<typename U>
		Mat<2, 2, T>& operator/=(U s);


	};


	//unary operators

	template<typename T>
	Mat<2, 2, T> operator+(const Mat<2, 2, T>& m);

	template<typename T>
	Mat<2, 2, T> operator-(const Mat<2, 2, T>& m);


	//binary operators

	template<typename T>
	Mat<2, 2, T> operator+(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2);

	template<typename T>
	Mat<2, 2, T> operator+(const Mat<2, 2, T>& m, T s);

	template<typename T>
	Mat<2, 2, T> operator+(T s, const Mat<2, 2, T>& m);

	template<typename T>
	Mat<2, 2, T> operator-(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2);

	template<typename T>
	Mat<2, 2, T> operator-(const Mat<2, 2, T>& m, T s);

	template<typename T>
	Mat<2, 2, T> operator-(T s, const Mat<2, 2, T>& m);


	//multiplication

	template<typename T>
	Mat<2, 2, T> operator*(const Mat<2, 2, T>& m, T s);

	template<typename T>
	Mat<2, 2, T> operator*(T s, const Mat<2, 2, T>& m);

	template<typename T>
	typename Mat<2, 2, T>::col_type operator*(const Mat<2, 2, T>& m, const typename Mat<2, 2, T>::row_type& v);

	template<typename T>
	typename Mat<2, 2, T>::col_type operator*(const typename Mat<2, 2, T>::row_type& v, const Mat<2, 2, T>& m);

	template<typename T>
	Mat<2, 2, T> operator*(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2);


	//division

	template<typename T>
	Mat<2, 2, T> operator/(const Mat<2, 2, T>& m, T s);

	template<typename T>
	Mat<2, 2, T> operator/(T s, const Mat<2, 2, T>& m);

	template<typename T>
	typename Mat<2, 2, T>::col_type operator/(const Mat<2, 2, T>& m, const typename Mat<2, 2, T>::row_type& v);

	template<typename T>
	typename Mat<2, 2, T>::col_type operator/(const typename Mat<2, 2, T>::row_type& v, const Mat<2, 2, T>& m);

	template<typename T>
	Mat<2, 2, T> operator/(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2);


	//boolean operators

	template<typename T>
	bool operator==(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2);

	template<typename T>
	bool operator!=(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2);

}

#include "mat2.inl"