namespace math {

	
	template<typename T>
	inline constexpr T& Vec<2, T>::operator[](int i)
	{
		switch (i) {
		default:
		case 0: return x;
		case 1: return y;
		}
	}

	template<typename T>
	inline constexpr const T& Vec<2, T>::operator[](int i) const
	{
		switch (i) {
		default:
		case 0: return x;
		case 1: return y;
		}
	}

	//constructors
	template<typename T>
	inline Vec<2, T>::Vec(T _x, T _y)
		: x(_x), y(_y)
	{}

	template<typename T>
	inline Vec<2, T>::Vec(T scalar)
		: x(scalar), y(scalar)
	{}

	
	//conversion constructors
	template<typename T>
	template<typename A, typename B>
	inline Vec<2, T>::Vec(A _x, B _y) :
		x(static_cast<T>(_x)),
		y(static_cast<T>(_y))
	{}

	//conversion vector constructors

	template<typename T>
	template<typename U>
	inline Vec<2, T>::Vec(const Vec<2, U>& v) :
		x(static_cast<T>(v.x)),
		y(static_cast<T>(v.y))
	{}

	template<typename T>
	template<typename U>
	inline Vec<2, T>::Vec(const Vec<3, U>& v) :
		x(static_cast<T>(v.x)),
		y(static_cast<T>(v.y))
	{}

	template<typename T>
	template<typename U>
	inline Vec<2, T>::Vec(const Vec<4, U>& v) :
		x(static_cast<T>(v.x)),
		y(static_cast<T>(v.y))
	{}


	//unary arithmetic operators

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator=(const Vec<2, U>& v) 
	{
		this->x = static_cast<T>(v.x);
		this->y = static_cast<T>(v.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator+=(const Vec<2, U>& v) 
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator+=(U scalar)
	{
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator-=(const Vec<2, U>& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator-=(U scalar)
	{
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator*=(const Vec<2, U>& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator*=(U scalar)
	{
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator/=(const Vec<2, U>& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>& Vec<2, T>::operator/=(U scalar)
	{
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		return *this;
	}

	//increment and decrement operators

	template<typename T>
	inline Vec<2, T>& Vec<2, T>::operator++()
	{
		++this->x;
		++this->y;
		return *this;
	}

	template<typename T>
	inline Vec<2, T>& Vec<2, T>::operator--()
	{
		--this->x;
		--this->y;
		return *this;
	}

	//unary arithmetic operators

	template<typename T>
	inline Vec<2, T> operator+(const Vec<2, T>& v)
	{
		return v;
	}

	template<typename T>
	inline Vec<2, T> operator-(const Vec<2, T>& v)
	{
		return Vec<2, T>(-v.x, -v.y);
	}
	

	//binary arithmetic operators

	template<typename T>
	inline Vec<2, T> operator+(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return Vec<2, T>(v1.x + v2.x, v1.y + v2.y);
	}

	template<typename T>
	inline Vec<2, T> operator+(const Vec<2, T>& v, T scalar)
	{
		return Vec<2, T>(v.x + scalar, v.y + scalar);
	}

	template<typename T>
	inline Vec<2, T> operator+(T scalar, const Vec<2, T>& v)
	{
		return Vec<2, T>(scalar + v.x, scalar + v.y);
	}


	template<typename T>
	inline Vec<2, T> operator-(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return Vec<2, T>(v1.x - v2.x, v1.y - v2.y);
	}

	template<typename T>
	inline Vec<2, T> operator-(const Vec<2, T>& v, T scalar)
	{
		return Vec<2, T>(v.x - scalar, v.y - scalar);
	}

	template<typename T>
	inline Vec<2, T> operator-(T scalar, const Vec<2, T>& v)
	{
		return Vec<2, T>(scalar - v.x, scalar - v.y);
	}


	template<typename T>
	inline Vec<2, T> operator*(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return Vec<2, T>(v1.x * v2.x, v1.y * v2.y);
	}

	template<typename T>
	inline Vec<2, T> operator*(const Vec<2, T>& v, T scalar)
	{
		return Vec<2, T>(v.x * scalar, v.y * scalar);
	}

	template<typename T>
	inline Vec<2, T> operator*(T scalar, const Vec<2, T>& v)
	{
		return Vec<2, T>(scalar * v.x, scalar * v.y);
	}


	template<typename T>
	inline Vec<2, T> operator/(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return Vec<2, T>(v1.x / v2.x, v1.y / v2.y);
	}

	template<typename T>
	inline Vec<2, T> operator/(const Vec<2, T>& v, T scalar)
	{
		return Vec<2, T>(v.x / scalar, v.y / scalar);
	}

	template<typename T>
	inline Vec<2, T> operator/(T scalar, const Vec<2, T>& v)
	{
		return Vec<2, T>(scalar / v.x, scalar / v.y);
	}


	//boolean operators

	template<typename T>
	inline bool operator==(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y;
	}

	template<typename T>
	inline bool operator!=(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return v1.x != v2.x || v1.y != v2.y;
	}

	template<typename T>
	inline bool operator>(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return v1.x > v2.x && v1.y > v2.y;
	}
	template<typename T>
	inline bool operator>=(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return v1.x >= v2.x && v1.y >= v2.y;
	}
	template<typename T>
	inline bool operator<(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return v1.x < v2.x && v1.y < v2.y;
	}
	template<typename T>
	inline bool operator<=(const Vec<2, T>& v1, const Vec<2, T>& v2)
	{
		return v1.x <= v2.x && v1.y <= v2.y;
	}

}