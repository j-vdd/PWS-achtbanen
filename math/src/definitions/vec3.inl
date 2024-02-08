namespace math {

	template<typename T>
	inline constexpr T& Vec<3, T>::operator[](int i)
	{
		switch (i) {
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		}
	}

	template<typename T>
	inline constexpr const T& Vec<3, T>::operator[](int i) const
	{
		switch (i) {
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		}
	}

	//constructors
	template<typename T>
	inline Vec<3, T>::Vec(T _x, T _y, T _z)
		: x(_x), y(_y), z(_z)
	{}

	template<typename T>
	inline Vec<3, T>::Vec(T scalar)
		: x(scalar), y(scalar), z(scalar)
	{}


	//conversion constructors
	template<typename T>
	template<typename A, typename B, typename C>
	inline Vec<3, T>::Vec(A _x, B _y, C _z) :
		x(static_cast<T>(_x)),
		y(static_cast<T>(_y)),
		z(static_cast<T>(_z))
	{}

	//conversion vector constructors

	template<typename T>
	template<typename U>
	inline Vec<3, T>::Vec(const Vec<3, U>& v) :
		x(static_cast<T>(v.x)),
		y(static_cast<T>(v.y)),
		z(static_cast<T>(v.z))
	{}

	template<typename T>
	template<typename U>
	inline Vec<3, T>::Vec(const Vec<4, U>& v) :
		x(static_cast<T>(v.x)),
		y(static_cast<T>(v.y)),
		z(static_cast<T>(v.z))
	{}

	template<typename T>
	template<typename U>
	inline Vec<3, T>::Vec(const Vec<2, U>& _xy, U _z) :
		x(static_cast<T>(_xy.x)),
		y(static_cast<T>(_xy.y)),
		z(static_cast<T>(_z))
	{}

	template<typename T>
	template<typename U>
	inline Vec<3, T>::Vec(U _x, const Vec<2, U>& _yz) :
		x(static_cast<T>(_x)),
		y(static_cast<T>(_yz.y)),
		z(static_cast<T>(_yz.z))
	{}


	//unary arithmetic operators

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator=(const Vec<3, U>& v)
	{
		this->x = static_cast<T>(v.x);
		this->y = static_cast<T>(v.y);
		this->z = static_cast<T>(v.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator+=(const Vec<3, U>& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		this->z += static_cast<T>(v.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator+=(U scalar)
	{
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator-=(const Vec<3, U>& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		this->z -= static_cast<T>(v.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator-=(U scalar)
	{
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator*=(const Vec<3, U>& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		this->z *= static_cast<T>(v.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator*=(U scalar)
	{
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator/=(const Vec<3, U>& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		this->z /= static_cast<T>(v.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<3, T>& Vec<3, T>::operator/=(U scalar)
	{
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		return *this;
	}

	//increment and decrement operators

	template<typename T>
	inline Vec<3, T>& Vec<3, T>::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	template<typename T>
	inline Vec<3, T>& Vec<3, T>::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	//unary arithmetic operators

	template<typename T>
	inline Vec<3, T> operator+(const Vec<3, T>& v)
	{
		return v;
	}

	template<typename T>
	inline Vec<3, T> operator-(const Vec<3, T>& v)
	{
		return Vec<3, T>(-v.x, -v.y, -v.z);
	}



	//binary arithmetic operators

	template<typename T>
	inline Vec<3, T> operator+(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return Vec<3, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	template<typename T>
	inline Vec<3, T> operator+(const Vec<3, T>& v, T scalar)
	{
		return Vec<3, T>(v.x + scalar, v.y + scalar, v.z + scalar);
	}

	template<typename T>
	inline Vec<3, T> operator+(T scalar, const Vec<3, T>& v)
	{
		return Vec<3, T>(scalar + v.x, scalar + v.y, scalar + v.z);
	}


	template<typename T>
	inline Vec<3, T> operator-(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return Vec<3, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	template<typename T>
	inline Vec<3, T> operator-(const Vec<3, T>& v, T scalar)
	{
		return Vec<3, T>(v.x - scalar, v.y - scalar, v.z - scalar);
	}

	template<typename T>
	inline Vec<3, T> operator-(T scalar, const Vec<3, T>& v)
	{
		return Vec<3, T>(scalar - v.x, scalar - v.y, scalar - v.z);
	}


	template<typename T>
	inline Vec<3, T> operator*(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return Vec<3, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	template<typename T>
	inline Vec<3, T> operator*(const Vec<3, T>& v, T scalar)
	{
		return Vec<3, T>(v.x * scalar, v.y * scalar, v.z * scalar);
	}

	template<typename T>
	inline Vec<3, T> operator*(T scalar, const Vec<3, T>& v)
	{
		return Vec<3, T>(scalar * v.x, scalar * v.y, scalar * v.z);
	}


	template<typename T>
	inline Vec<3, T> operator/(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return Vec<3, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
	}

	template<typename T>
	inline Vec<3, T> operator/(const Vec<3, T>& v, T scalar)
	{
		return Vec<3, T>(v.x / scalar, v.y / scalar, v.z / scalar);
	}

	template<typename T>
	inline Vec<3, T> operator/(T scalar, const Vec<3, T>& v)
	{
		return Vec<3, T>(scalar / v.x, scalar / v.y, scalar / v.z);
	}


	//boolean operators

	template<typename T>
	inline bool operator==(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}

	template<typename T>
	inline bool operator!=(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
	}

	template<typename T>
	inline bool operator>(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z;
	}
	template<typename T>
	inline bool operator>=(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z;
	}
	template<typename T>
	inline bool operator<(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return v1.x < v2.x&& v1.y < v2.y && v1.z < v2.z;
	}
	template<typename T>
	inline bool operator<=(const Vec<3, T>& v1, const Vec<3, T>& v2)
	{
		return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z;
	}

}