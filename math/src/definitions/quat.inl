#include "../geometric.h"
#include "../trigonometric.h"

namespace math {

	template<typename T>
	constexpr T& Quat<T>::operator[](int i)
	{
		return (&s)[i];
	}

	template<typename T>
	constexpr T const& Quat<T>::operator[](int i) const
	{
		return (&s)[i];
	}


	//basic constructors

	template<typename T>
	inline constexpr math::Quat<T>::Quat(T _s, const Vec<3, T>& v) :
		s(_s), x(v.x), y(v.y), z(v.z)
	{}

	template<typename T>
	inline constexpr Quat<T>::Quat(T _s, T _x, T _y, T _z) :
		s(_s), x(_x), y(_y), z(_z)
	{}


	//conversion constructors

	template<typename T>
	template<typename U>
	inline constexpr Quat<T>::Quat(const Quat<U>& q) :
		s(static_cast<T>(q.s)), x(static_cast<T>(q.x)), y(static_cast<T>(q.y)), z(static_cast<T>(q.z))
	{}

	template<typename T>
	template<typename A, typename B, typename C, typename D>
	inline constexpr math::Quat<T>::Quat(A _s, B _x, C _y, D _z) :
		s(static_cast<T>(_s)), x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z))
	{}

	template<typename T>
	inline Quat<T>::Quat(const Vec<3, T>& u, const Vec<3, T>& v) 
	{
		T norm_u_norm_v = sqrt(dot(u, u) * dot(v, v));
		T real_part = norm_u_norm_v + dot(u, v);
		Vec<3, T> t;

		if (real_part < static_cast<T>(1.e-6f) * norm_u_norm_v)
		{
			// If u and v are exactly opposite, rotate 180 degrees
			// around an arbitrary orthogonal axis. Axis normalisation
			// can happen later, when we normalise the quaternion.
			real_part = static_cast<T>(0);
			t = abs(u.x) > abs(u.z) ? Vec<3, T>(-u.y, u.x, static_cast<T>(0)) : Vec<3, T>(static_cast<T>(0), -u.z, u.y);
		}
		else
		{
			// Otherwise, build quaternion the standard way.
			t = cross(u, v);
		}

		*this = normalize(Quat<T>(real_part, t));
	}

	template<typename T>
	inline Quat<T>::Quat(const Vec<3, T>& eulerAngle) 
	{
		Vec<3, T> C(cos(eulerAngle * static_cast<T>(0.5)));
		Vec<3, T> S(sin(eulerAngle * static_cast<T>(0.5)));

		this->s = C.x * C.y * C.z + S.x * S.y * S.z;
		this->x = S.x * C.y * C.z - C.x * S.y * S.z;
		this->y = C.x * S.y * C.z + S.x * C.y * S.z;
		this->z = C.x * C.y * S.z - S.x * S.y * C.z;
	}

	template<typename T>
	inline Quat<T>::Quat(const Mat<3, 3, T>& m)
	{
		*this = quat_cast(m);
	}

	template<typename T>
	inline Quat<T>::Quat(const Mat<4, 4, T>& m)
	{
		*this = quat_cast(m);
	}


	//conversion operators

	template<typename T>
	inline Quat<T>::operator Mat<3, 3, T>() const
	{
		return mat3_cast(*this);
	}

	template<typename T>
	inline Quat<T>::operator Mat<4, 4, T>() const
	{
		return mat4_cast(*this);
	}


	//unary arithmetic operators

	template<typename T>
	template<typename U>
	inline Quat<T>& Quat<T>::operator=(const Quat<U>& q) {
		this->s = static_cast<T>(q.s);
		this->x = static_cast<T>(q.x);
		this->y = static_cast<T>(q.y);
		this->z = static_cast<T>(q.z);

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Quat<T>& Quat<T>::operator+=(const Quat<U>& q)
	{
		this->s += static_cast<T>(q.s);
		this->x += static_cast<T>(q.x);
		this->y += static_cast<T>(q.y);
		this->z += static_cast<T>(q.z);

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Quat<T>& Quat<T>::operator-=(const Quat<U>& q)
	{
		this->s -= static_cast<T>(q.s);
		this->x -= static_cast<T>(q.x);
		this->y -= static_cast<T>(q.y);
		this->z -= static_cast<T>(q.z);

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Quat<T>& Quat<T>::operator*=(const Quat<U>& r)
	{
		const Quat<T> p(*this);
		const Quat<T> q(r);

		this->s = p.s * q.s - p.x * q.x - p.y * q.y - p.z * q.z;
		this->x = p.s * q.x + p.x * q.s + p.y * q.z - p.z * q.y;
		this->y = p.s * q.y + p.y * q.s + p.z * q.x - p.x * q.z;
		this->z = p.s * q.z + p.z * q.s + p.x * q.y - p.y * q.x;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Quat<T>& Quat<T>::operator*=(U _s)
	{
		this->s *= static_cast<T>(_s);
		this->x *= static_cast<T>(_s);
		this->y *= static_cast<T>(_s);
		this->z *= static_cast<T>(_s);

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Quat<T>& Quat<T>::operator/=(U _s)
	{
		this->s /= static_cast<T>(_s);
		this->x /= static_cast<T>(_s);
		this->y /= static_cast<T>(_s);
		this->z /= static_cast<T>(_s);

		return *this;
	}


	//unary bit operators

	template<typename T>
	inline Quat<T> operator+(Quat<T> const& q)
	{
		return q;
	}

	template<typename T>
	inline Quat<T> operator-(Quat<T> const& q)
	{
		return Quat<T>(-q.s, -q.x, -q.y, -q.z);
	}


	//binary operators

	template<typename T>
	inline Quat<T> operator+(Quat<T> const& p, Quat<T> const& q)
	{
		return Quat<T>(p.s + q.s, p.x + q.x, p.y + q.y, p.z + q.z);
	}

	template<typename T>
	inline Quat<T> operator-(Quat<T> const& p, Quat<T> const& q)
	{
		return Quat<T>(p.s - q.s, p.x - q.x, p.y - q.y, p.z - q.z);
	}

	template<typename T>
	inline Quat<T> operator*(Quat<T> const& p, Quat<T> const& q)
	{
		return Quat<T>(
			p.s * q.s - p.x * q.x - p.y * q.y - p.z * q.z,
			p.s * q.x + p.x * q.s + p.y * q.z - p.z * q.y,
			p.s * q.y + p.y * q.s + p.z * q.x - p.x * q.z,
			p.s * q.z + p.z * q.s + p.x * q.y - p.y * q.x
		);
	}


	template<typename T>
	inline Vec<3, T> operator*(Quat<T> const& q, Vec<3, T> const& v)
	{
		const Vec<3, T> QuatVector(q.x, q.y, q.z);
		const Vec<3, T> uv(cross(QuatVector, v));
		const Vec<3, T> uuv(cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * static_cast<T>(2);
	}

	template<typename T>
	inline Vec<3, T> operator*(Vec<3, T> const& v, Quat<T> const& q)
	{
		return inverse(q) * v;
	}


	template<typename T>
	inline Vec<4, T> operator*(Quat<T> const& q, Vec<4, T> const& v)
	{
		return Vec<4, T>(q * Vec<3, T>(v), v.w);
	}

	template<typename T>
	inline Vec<4, T> operator*(Vec<4, T> const& v, Quat<T> const& q)
	{
		return inverse(q) * v;
	}


	template<typename T>
	inline Quat<T> operator*(Quat<T> const& q, T const& s)
	{
		return Quat<T>(q.s * s, q.x * s, q.y * s, q.z * s);
	}

	template<typename T>
	inline Quat<T> operator*(T const& s, Quat<T> const& q)
	{
		return Quat<T>(s * q.s, s * q.x, s * q.y, s * q.z);
	}

	template<typename T>
	inline Quat<T> operator/(Quat<T> const& q, T const& s)
	{
		return Quat<T>(q.s / s, q.x / s, q.y / s, q.z / s);
	}


	//boolean operators

	template<typename T>
	inline bool operator==(Quat<T> const& q1, Quat<T> const& q2)
	{
		return q1.s == q2.s && q1.x == q2.x && q1.y == q2.y && q1.z == q2.z;
	}

	template<typename T>
	inline bool operator!=(Quat<T> const& q1, Quat<T> const& q2)
	{
		return q1.s != q2.s || q1.x != q2.x || q1.y != q2.y || q1.z != q2.z;
	}


}