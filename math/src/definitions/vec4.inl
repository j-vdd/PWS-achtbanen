namespace math {

	template<typename T>
	inline constexpr T& Vec<4, T>::operator[](int i)
	{
		switch (i) {
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		}
	}

	template<typename T>
	inline constexpr const T& Vec<4, T>::operator[](int i) const
	{
		switch (i) {
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		}
	}

	//constructors
	template<typename T>
	inline Vec<4, T>::Vec(T _x, T _y, T _z, T _w)
		: x(_x), y(_y), z(_z), w(_w)
	{}

	template<typename T>
	inline Vec<4, T>::Vec(T scalar)
		: x(scalar), y(scalar), z(scalar), w(scalar)
	{}


	//conversion constructors
	template<typename T>
	template<typename A, typename B, typename C, typename D>
	inline Vec<4, T>::Vec(A _x, B _y, C _z, D _w) :
		x(static_cast<T>(_x)),
		y(static_cast<T>(_y)),
		z(static_cast<T>(_z)),
		w(static_cast<T>(_w))
	{}

	//conversion vector constructors

	template<typename T>
	template<typename U>
	inline Vec<4, T>::Vec(const Vec<4, U>& v) :
		x(static_cast<T>(v.x)),
		y(static_cast<T>(v.y)),
		z(static_cast<T>(v.z)),
		w(static_cast<T>(v.w))
	{}

	template<typename T>
	template<typename U>
	inline Vec<4, T>::Vec(const Vec<2, U>& _xy, const Vec<2, U>& _zw) :
		x(static_cast<T>(_xy.x)),
		y(static_cast<T>(_xy.y)),
		z(static_cast<T>(_zw.z)),
		w(static_cast<T>(_zw.w))
	{}

	template<typename T>
	template<typename U>
	inline Vec<4, T>::Vec(const Vec<3, U>& _xyz, U _w) :
		x(static_cast<T>(_xyz.x)),
		y(static_cast<T>(_xyz.y)),
		z(static_cast<T>(_xyz.z)),
		w(static_cast<T>(_w))
	{}

	template<typename T>
	template<typename U>
	inline Vec<4, T>::Vec(U _x, const Vec<3, U>& _yzw) :
		x(static_cast<T>(_x)),
		y(static_cast<T>(_yzw.y)),
		z(static_cast<T>(_yzw.z)),
		w(static_cast<T>(_yzw.w))
	{}

	template<typename T>
	template<typename U>
	inline Vec<4, T>::Vec(const Vec<2, U>& _xy, U _z, U _w) :
		x(static_cast<T>(_xy.x)),
		y(static_cast<T>(_xy.y)),
		z(static_cast<T>(_z)),
		w(static_cast<T>(_w))
	{}

	template<typename T>
	template<typename U>
	inline Vec<4, T>::Vec(U _x, const Vec<2, U>& _yz, U _w) :
		x(static_cast<T>(_x)),
		y(static_cast<T>(_yz.y)),
		z(static_cast<T>(_yz.z)),
		w(static_cast<T>(_w))
	{}

	template<typename T>
	template<typename U>
	inline Vec<4, T>::Vec(U _x, U _y, const Vec<2, U>& _zw) :
		x(static_cast<T>(_x)),
		y(static_cast<T>(_y)),
		z(static_cast<T>(_zw.z)),
		w(static_cast<T>(_zw.w))
	{}


	//unary arithmetic operators

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator=(const Vec<4, U>& v)
	{
		this->x = static_cast<T>(v.x);
		this->y = static_cast<T>(v.y);
		this->z = static_cast<T>(v.z);
		this->w = static_cast<T>(v.w);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator+=(const Vec<4, U>& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		this->z += static_cast<T>(v.z);
		this->w += static_cast<T>(v.w);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator+=(U scalar)
	{
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		this->w += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator-=(const Vec<4, U>& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		this->z -= static_cast<T>(v.z);
		this->w -= static_cast<T>(v.w);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator-=(U scalar)
	{
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		this->w -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator*=(const Vec<4, U>& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		this->z *= static_cast<T>(v.z);
		this->w *= static_cast<T>(v.w);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator*=(U scalar)
	{
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		this->w *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator/=(const Vec<4, U>& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		this->z /= static_cast<T>(v.z);
		this->w /= static_cast<T>(v.w);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<4, T>& Vec<4, T>::operator/=(U scalar)
	{
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		this->w /= static_cast<T>(scalar);
		return *this;
	}

	//increment and decrement operators

	template<typename T>
	inline Vec<4, T>& Vec<4, T>::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}

	template<typename T>
	inline Vec<4, T>& Vec<4, T>::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
	}

	//unary arithmetic operators

	template<typename T>
	inline Vec<4, T> operator+(const Vec<4, T>& v)
	{
		return v;
	}

	template<typename T>
	inline Vec<4, T> operator-(const Vec<4, T>& v)
	{
		return Vec<4, T>(-v.x, -v.y, -v.z, -v.w);
	}



	//binary arithmetic operators

	template<typename T>
	inline Vec<4, T> operator+(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return Vec<4, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	template<typename T>
	inline Vec<4, T> operator+(const Vec<4, T>& v, T scalar)
	{
		return Vec<4, T>(v.x + scalar, v.y + scalar, v.z + scalar, v.w + scalar);
	}

	template<typename T>
	inline Vec<4, T> operator+(T scalar, const Vec<4, T>& v)
	{
		return Vec<4, T>(scalar + v.x, scalar + v.y, scalar + v.z, scalar + v.w);
	}


	template<typename T>
	inline Vec<4, T> operator-(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return Vec<4, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}

	template<typename T>
	inline Vec<4, T> operator-(const Vec<4, T>& v, T scalar)
	{
		return Vec<4, T>(v.x - scalar, v.y - scalar, v.z - scalar, v.w - scalar);
	}

	template<typename T>
	inline Vec<4, T> operator-(T scalar, const Vec<4, T>& v)
	{
		return Vec<4, T>(scalar - v.x, scalar - v.y, scalar - v.z, scalar - v.w);
	}


	template<typename T>
	inline Vec<4, T> operator*(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return Vec<4, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}

	template<typename T>
	inline Vec<4, T> operator*(const Vec<4, T>& v, T scalar)
	{
		return Vec<4, T>(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
	}

	template<typename T>
	inline Vec<4, T> operator*(T scalar, const Vec<4, T>& v)
	{
		return Vec<4, T>(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
	}


	template<typename T>
	inline Vec<4, T> operator/(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return Vec<4, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
	}

	template<typename T>
	inline Vec<4, T> operator/(const Vec<4, T>& v, T scalar)
	{
		return Vec<3, T>(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
	}

	template<typename T>
	inline Vec<4, T> operator/(T scalar, const Vec<4, T>& v)
	{
		return Vec<3, T>(scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
	}


	//boolean operators

	template<typename T>
	inline bool operator==(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
	}

	template<typename T>
	inline bool operator!=(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
	}

	template<typename T>
	inline bool operator>(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z && v1.w > v2.w;
	}
	template<typename T>
	inline bool operator>=(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z && v1.w >= v2.w;
	}
	template<typename T>
	inline bool operator<(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return v1.x < v2.x&& v1.y < v2.y&& v1.z < v2.z && v1.w < v2.w;
	}
	template<typename T>
	inline bool operator<=(const Vec<4, T>& v1, const Vec<4, T>& v2)
	{
		return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z && v1.w <= v2.w;
	}

}