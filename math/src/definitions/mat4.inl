#include "../func_matrix.h"

namespace math {

	//accesses

	template<typename T>
	inline typename Mat<4, 4, T>::col_type& Mat<4, 4, T>::operator[](int i)
	{
		return this->value[i];
	}

	template<typename T>
	inline constexpr typename Mat<4, 4, T>::col_type const& Mat<4, 4, T>::operator[](int i) const
	{
		return this->value[i];
	}


	//constructors

	template<typename T>
	inline constexpr Mat<4, 4, T>::Mat(const T& s)
		: value{ col_type(s, 0, 0, 0), col_type(0, s, 0, 0), col_type(0, 0, s, 0), col_type(0, 0, 0, s) }
	{}

	template<typename T>
	inline constexpr Mat<4, 4, T>::Mat(
		const T& x0, const T& y0, const T& z0, const T& w0,
		const T& x1, const T& y1, const T& z1, const T& w1,
		const T& x2, const T& y2, const T& z2, const T& w2,
		const T& x3, const T& y3, const T& z3, const T& w3
	) : value{
		col_type(x0, y0, z0, w0),
		col_type(x1, y1, z1, w1),
		col_type(x2, y2, z2, w2),
		col_type(x3, y3, z3, w3)
	}
	{}

	template<typename T>
	inline constexpr Mat<4, 4, T>::Mat(const col_type& v0, const col_type& v1, const col_type& v2, const col_type& v3)
		: value{ v0, v1, v2, v3 }
	{}


	//conversions

	template<typename T>
	template<
		typename X0, typename Y0, typename Z0, typename W0,
		typename X1, typename Y1, typename Z1, typename W1,
		typename X2, typename Y2, typename Z2, typename W2,
		typename X3, typename Y3, typename Z3, typename W3
	>
	inline constexpr Mat<4, 4, T>::Mat(
		const X0& x0, const Y0& y0, const Z0& z0, const W0& w0,
		const X1& x1, const Y1& y1, const Z1& z1, const W1& w1,
		const X2& x2, const Y2& y2, const Z2& z2, const W2& w2,
		const X3& x3, const Y3& y3, const Z3& z3, const W3& w3
	) : value{
		col_type(x0, y0, z0, w0),
		col_type(x1, y1, z1, w1),
		col_type(x2, y2, z2, w2),
		col_type(x3, y3, z3, w3)
	}
	{}

	template<typename T>
	template<typename V0, typename V1, typename V2, typename V3>
	inline constexpr Mat<4, 4, T>::Mat(const Vec<4, V0>& v0, const Vec<4, V1>& v1, const Vec<4, V2>& v2, const Vec<4, V3>& v3)
		: value{ col_type(v0), col_type(v1), col_type(v2), col_type(v3) }
	{}


	//matrix conversions

	template<typename T>
	template<typename U>
	inline constexpr Mat<4, 4, T>::Mat(const Mat<4, 4, U>& m)
		: value{ col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3]) }
	{}

	template<typename T>
	inline constexpr Mat<4, 4, T>::Mat(const Mat<2, 2, T>& m)
		: value{ col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1) }
	{}
	template<typename T>
	inline constexpr Mat<4, 4, T>::Mat(const Mat<3, 3, T>& m)
		: value{ 
			col_type(m[0][0], m[0][1], m[0][2], 0), 
			col_type(m[1][0], m[1][1], m[1][2], 0), 
			col_type(m[2][0], m[2][1], m[2][2], 0), 
			col_type(0, 0, 0, 1)
		}
	{}


	//unary arithmetic operators

	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& Mat<4, 4, T>::operator=(const Mat<4, 4, U>& m) 
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		this->value[3] = m[3];

		return *this;
	}
	

	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& math::Mat<4, 4, T>::operator+=(const Mat<4, 4, U>& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		this->value[3] += m[3];

		return *this;
	}
	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& math::Mat<4, 4, T>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		this->value[3] += s;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& math::Mat<4, 4, T>::operator-=(const Mat<4, 4, U>& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		this->value[3] -= m[3];

		return *this;
	}
	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& math::Mat<4, 4, T>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		this->value[3] -= s;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& math::Mat<4, 4, T>::operator*=(const Mat<4, 4, U>& m)
	{
		*this = *this * m;

		return *this;
	}
	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& math::Mat<4, 4, T>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		this->value[3] *= s;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& math::Mat<4, 4, T>::operator/=(const Mat<4, 4, U>& m)
	{
		*this = *this * inverse(m);

		return *this;
	}
	template<typename T>
	template<typename U>
	inline Mat<4, 4, T>& math::Mat<4, 4, T>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		this->value[3] /= s;

		return *this;
	}

	//unary operators

	template<typename T>
	inline Mat<4, 4, T> operator+(const Mat<4, 4, T>& m) 
	{
		return m;
	}

	template<typename T>
	inline Mat<4, 4, T> operator-(const Mat<4, 4, T>& m) 
	{
		return Mat<4, 4, T>(-m[0], -m[1], -m[2], -m[3]);
	}


	//binary operators

	//addition

	template<typename T>
	inline Mat<4, 4, T> operator+(const Mat<4, 4, T>& m1, const Mat<4, 4, T>& m2)
	{
		return Mat<4, 4, T>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2],
			m1[3] + m2[3]
		);
	}
	template<typename T>
	inline Mat<4, 4, T> operator+(const Mat<4, 4, T>& m, T s)
	{
		return Mat<4, 4, T>(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s
		);
	}
	template<typename T>
	inline Mat<4, 4, T> operator+(T s, const Mat<4, 4, T>& m)
	{
		return Mat<4, 4, T>(
			s + m[0],
			s + m[1],
			s + m[2],
			s + m[3]
		);
	}


	//subtraction

	template<typename T>
	inline Mat<4, 4, T> operator-(const Mat<4, 4, T>& m1, const Mat<4, 4, T>& m2)
	{
		return Mat<4, 4, T>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2],
			m1[3] - m2[3]
		);
	}
	template<typename T>
	inline Mat<4, 4, T> operator-(const Mat<4, 4, T>& m, T s)
	{
		return Mat<4, 4, T>(
			m[0] - s,
			m[1] - s,
			m[2] - s,
			m[3] - s
		);
	}
	template<typename T>
	inline Mat<4, 4, T> operator-(T s, const Mat<4, 4, T>& m)
	{
		return Mat<4, 4, T>(
			s - m[0],
			s - m[1],
			s - m[2],
			s - m[3]
		);
	}


	//multiplication

	template<typename T>
	inline Mat<4, 4, T> operator*(const Mat<4, 4, T>& m, T s)
	{
		return Mat<4, 4, T>(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s
		);
	}
	template<typename T>
	inline Mat<4, 4, T> operator*(T s, const Mat<4, 4, T>& m)
	{
		return Mat<4, 4, T>(
			s * m[0],
			s * m[1],
			s * m[2],
			s * m[3]
		);
	}
	template<typename T>
	inline typename Mat<4, 4, T>::col_type operator*(const Mat<4, 4, T>& m, const typename Mat<4, 4, T>::row_type& v)
	{
		typename Mat<4, 4, T>::col_type const Mov0(v[0]);
		typename Mat<4, 4, T>::col_type const Mov1(v[1]);
		typename Mat<4, 4, T>::col_type const Mul0 = m[0] * Mov0;
		typename Mat<4, 4, T>::col_type const Mul1 = m[1] * Mov1;
		typename Mat<4, 4, T>::col_type const Add0 = Mul0 + Mul1;
		typename Mat<4, 4, T>::col_type const Mov2(v[2]);
		typename Mat<4, 4, T>::col_type const Mov3(v[3]);
		typename Mat<4, 4, T>::col_type const Mul2 = m[2] * Mov2;
		typename Mat<4, 4, T>::col_type const Mul3 = m[3] * Mov3;
		typename Mat<4, 4, T>::col_type const Add1 = Mul2 + Mul3;
		typename Mat<4, 4, T>::col_type const Add2 = Add0 + Add1;

		return Add2;
	}
	template<typename T>
	inline typename Mat<4, 4, T>::col_type operator*(const typename Mat<4, 4, T>::row_type& v, const Mat<4, 4, T>& m)
	{
		return typename Mat<4, 4, T>::row_type(
			m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
			m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
			m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
			m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]);
	}
	template<typename T>
	inline Mat<4, 4, T> operator*(const Mat<4, 4, T>& m1, const Mat<4, 4, T>& m2)
	{
		typename Mat<4, 4, T>::col_type const SrcA0 = m1[0];
		typename Mat<4, 4, T>::col_type const SrcA1 = m1[1];
		typename Mat<4, 4, T>::col_type const SrcA2 = m1[2];
		typename Mat<4, 4, T>::col_type const SrcA3 = m1[3];

		typename Mat<4, 4, T>::col_type const SrcB0 = m2[0];
		typename Mat<4, 4, T>::col_type const SrcB1 = m2[1];
		typename Mat<4, 4, T>::col_type const SrcB2 = m2[2];
		typename Mat<4, 4, T>::col_type const SrcB3 = m2[3];

		Mat<4, 4, T> Result;
		Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
		Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
		Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
		Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
		return Result;
	}


	//division
	template<typename T>
	inline Mat<4, 4, T> operator/(const Mat<4, 4, T>& m, T s)
	{
		return Mat<4, 4, T>(
			m[0] / s,
			m[1] / s,
			m[2] / s,
			m[3] / s
		);
	}
	template<typename T>
	inline Mat<4, 4, T> operator/(T s, const Mat<4, 4, T>& m)
	{
		return Mat<4, 4, T>(
			s / m[0],
			s / m[1],
			s / m[2],
			s / m[3]
		);
	}
	template<typename T>
	inline typename Mat<4, 4, T>::col_type operator/(const Mat<4, 4, T>& m, const typename Mat<4, 4, T>::row_type& v)
	{
		return inverse(m) * v;
	}
	template<typename T>
	inline typename Mat<4, 4, T>::col_type operator/(const typename Mat<4, 4, T>::row_type& v, const Mat<4, 4, T>& m)
	{
		return v * inverse(m);
	}
	template<typename T>
	inline Mat<4, 4, T> operator/(const Mat<4, 4, T>& m1, const Mat<4, 4, T>& m2)
	{
		return m1 * inverse(m2);
	}


	//boolean operators

	template<typename T>
	inline bool operator==(const Mat<4, 4, T>& m1, const Mat<4, 4, T>& m2)
	{
		return m1[0] == m2[0] && m1[1] == m2[1] && m1[2] == m2[2] && m1[3] == m2[3];
	}
	template<typename T>
	inline bool operator!=(const Mat<4, 4, T>& m1, const Mat<4, 4, T>& m2)
	{
		return m1[0] != m2[0] || m1[1] != m2[1] || m1[2] != m2[2] || m1[3] != m2[3];
	}

}