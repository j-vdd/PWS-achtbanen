#include "../func_matrix.h"

namespace math {

	//accesses

	template<typename T>
	inline typename Mat<2, 2, T>::col_type& Mat<2, 2, T>::operator[](int i)
	{
		return this->value[i];
	}

	template<typename T>
	inline constexpr typename Mat<2, 2, T>::col_type const& Mat<2, 2, T>::operator[](int i) const
	{
		return this->value[i];
	}


	//constructors

	template<typename T>
	inline constexpr Mat<2, 2, T>::Mat(const T& s)
		: value{ col_type(s, 0), col_type(0, s) }
	{}

	template<typename T>
	inline constexpr Mat<2, 2, T>::Mat(
		const T& x0, const T& y0,
		const T& x1, const T& y1
	) : value{
		col_type(x0, y0),
		col_type(x1, y1)
	}
	{}

	template<typename T>
	inline constexpr Mat<2, 2, T>::Mat(const col_type& v0, const col_type& v1)
		: value{ v0, v1 }
	{}


	//conversions

	template<typename T>
	template<
		typename X0, typename Y0,
		typename X1, typename Y1
	>
	inline constexpr Mat<2, 2, T>::Mat(
		const X0& x0, const Y0& y0,
		const X1& x1, const Y1& y1
	) : value(
		col_type(x0, y0),
		col_type(x1, y1)
	)
	{}

	template<typename T>
	template<typename V0, typename V1>
	inline constexpr Mat<2, 2, T>::Mat(const Vec<2, V0>& v0, const Vec<2, V1>& v1)
		: value{ col_type(v0), col_type(v1) }
	{}


	//matrix conversions

	template<typename T>
	template<typename U>
	inline constexpr Mat<2, 2, T>::Mat(const Mat<2, 2, U>& m)
		: value{ col_type(m[0]), col_type(m[1]) }
	{}

	template<typename T>
	inline constexpr Mat<2, 2, T>::Mat(const Mat<3, 3, T>& m)
		: value{ col_type(m[0]), col_type(m[1]) }
	{}
	template<typename T>
	inline constexpr Mat<2, 2, T>::Mat(const Mat<4, 4, T>& m)
		: value{ col_type(m[0]), col_type(m[1]) }
	{}


	//unary arithmetic operators

	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& Mat<2, 2, T>::operator=(const Mat<2, 2, U>& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		
		return *this;
	}


	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& math::Mat<2, 2, T>::operator+=(const Mat<2, 2, U>& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		
		return *this;
	}
	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& math::Mat<2, 2, T>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& math::Mat<2, 2, T>::operator-=(const Mat<2, 2, U>& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		
		return *this;
	}
	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& math::Mat<2, 2, T>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& math::Mat<2, 2, T>::operator*=(const Mat<2, 2, U>& m)
	{
		*this = *this * m;

		return *this;
	}
	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& math::Mat<2, 2, T>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& math::Mat<2, 2, T>::operator/=(const Mat<2, 2, U>& m)
	{
		*this = *this * inverse(m);

		return *this;
	}
	template<typename T>
	template<typename U>
	inline Mat<2, 2, T>& math::Mat<2, 2, T>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		
		return *this;
	}


	//unary operators

	template<typename T>
	inline Mat<2, 2, T> operator+(const Mat<2, 2, T>& m)
	{
		return m;
	}

	template<typename T>
	inline Mat<2, 2, T> operator-(const Mat<2, 2, T>& m)
	{
		return Mat<2, 2, T>(-m[0], -m[1]);
	}


	//binary operators

	//addition

	template<typename T>
	inline Mat<2, 2, T> operator+(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2)
	{
		return Mat<2, 2, T>(
			m1[0] + m2[0],
			m1[1] + m2[1]
		);
	}
	template<typename T>
	inline Mat<2, 2, T> operator+(const Mat<2, 2, T>& m, T s)
	{
		return Mat<2, 2, T>(
			m[0] + s,
			m[1] + s
		);
	}
	template<typename T>
	inline Mat<2, 2, T> operator+(T s, const Mat<2, 2, T>& m)
	{
		return Mat<2, 2, T>(
			s + m[0],
			s + m[1]
		);
	}


	//subtraction

	template<typename T>
	inline Mat<2, 2, T> operator-(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2)
	{
		return Mat<2, 2, T>(
			m1[0] - m2[0],
			m1[1] - m2[1]
		);
	}
	template<typename T>
	inline Mat<2, 2, T> operator-(const Mat<2, 2, T>& m, T s)
	{
		return Mat<2, 2, T>(
			m[0] - s,
			m[1] - s
		);
	}
	template<typename T>
	inline Mat<2, 2, T> operator-(T s, const Mat<2, 2, T>& m)
	{
		return Mat<2, 2, T>(
			s - m[0],
			s - m[1]
		);
	}


	//multiplication

	template<typename T>
	inline Mat<2, 2, T> operator*(const Mat<2, 2, T>& m, T s)
	{
		return Mat<2, 2, T>(
			m[0] * s,
			m[1] * s
		);
	}
	template<typename T>
	inline Mat<2, 2, T> operator*(T s, const Mat<2, 2, T>& m)
	{
		return Mat<2, 2, T>(
			s * m[0],
			s * m[1]
		);
	}
	template<typename T>
	inline typename Mat<2, 2, T>::col_type operator*(const Mat<2, 2, T>& m, const typename Mat<2, 2, T>::row_type& v)
	{
		return typename Mat<2, 2, T>::col_type(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y);
	}
	template<typename T>
	inline typename Mat<2, 2, T>::col_type operator*(const typename Mat<2, 2, T>::row_type& v, const Mat<2, 2, T>& m)
	{
		return typename Mat<2, 2, T>::row_type(
			m[0][0] * v.x + m[0][1] * v.y,
			m[1][0] * v.x + m[1][1] * v.y);
	}
	template<typename T>
	inline Mat<2, 2, T> operator*(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2)
	{
		typename Mat<2, 2, T>::col_type const SrcA0 = m1[0];
		typename Mat<2, 2, T>::col_type const SrcA1 = m1[1];
		
		typename Mat<2, 2, T>::col_type const SrcB0 = m2[0];
		typename Mat<2, 2, T>::col_type const SrcB1 = m2[1];
		
		Mat<2, 2, T> Result;
		Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1];
		Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1];
		return Result;
	}


	//division

	template<typename T>
	inline Mat<2, 2, T> operator/(const Mat<2, 2, T>& m, T s)
	{
		return Mat<2, 2, T>(
			m[0] / s,
			m[1] / s
		);
	}
	template<typename T>
	inline Mat<2, 2, T> operator/(T s, const Mat<2, 2, T>& m)
	{
		return Mat<2, 2, T>(
			s / m[0],
			s / m[1]
		);
	}
	template<typename T>
	inline typename Mat<2, 2, T>::col_type operator/(const Mat<2, 2, T>& m, const typename Mat<2, 2, T>::row_type& v)
	{
		return inverse(m) * v;
	}
	template<typename T>
	inline typename Mat<2, 2, T>::col_type operator/(const typename Mat<2, 2, T>::row_type& v, const Mat<2, 2, T>& m)
	{
		return v * inverse(m);
	}
	template<typename T>
	inline Mat<2, 2, T> operator/(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2)
	{
		return m1 * inverse(m2);
	}


	//boolean operators

	template<typename T>
	inline bool operator==(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2)
	{
		return m1[0] == m2[0] && m1[1] == m2[1];
	}
	template<typename T>
	inline bool operator!=(const Mat<2, 2, T>& m1, const Mat<2, 2, T>& m2)
	{
		return m1[0] != m2[0] || m1[1] != m2[1];
	}

}