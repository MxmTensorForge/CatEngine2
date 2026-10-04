namespace Mxm {
	////////////
	/// Vec2i ///
	////////////
	constexpr Vec2i::Vec2i() noexcept : x{ 0 }, y{ 0 } {}
	constexpr Vec2i::Vec2i(int s) noexcept : x{ s }, y{ s } {}
	constexpr Vec2i::Vec2i(int vx, int vy) noexcept : x{ vx }, y{ vy } {}

	inline int& Vec2i::operator[](size_t index) noexcept {
		assert(index < 2);
		return (&x)[index];
	}
	inline const int& Vec2i::operator[](size_t index) const noexcept {
		assert(index < 2);
		return (&x)[index];
	}

	inline Vec2i Vec2i::operator+(const Vec2i& vec) const noexcept {
		return Vec2i(x + vec.x, y + vec.y);
	}
	inline Vec2i Vec2i::operator-(const Vec2i& vec) const noexcept {
		return Vec2i(x - vec.x, y - vec.y);
	}
	inline Vec2i Vec2i::operator*(const Vec2i& vec) const noexcept {
		return Vec2i(x * vec.x, y * vec.y);
	}
	inline Vec2i Vec2i::operator/(const Vec2i& vec) const noexcept {
		return Vec2i(x / vec.x, y / vec.y);
	}
	inline Vec2i& Vec2i::operator+=(const Vec2i& vec) noexcept {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	inline Vec2i& Vec2i::operator-=(const Vec2i& vec) noexcept {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	inline Vec2i& Vec2i::operator*=(const Vec2i& vec) noexcept {
		x *= vec.x;
		y *= vec.y;
		return *this;
	}
	inline Vec2i& Vec2i::operator/=(const Vec2i& vec) noexcept {
		x /= vec.x;
		y /= vec.y;
		return *this;
	}

	inline Vec2i Vec2i::operator+(int s) const noexcept {
		return Vec2i(x + s, y + s);
	}
	inline Vec2i Vec2i::operator-(int s) const noexcept {
		return Vec2i(x - s, y - s);
	}
	inline Vec2i Vec2i::operator*(int s) const noexcept {
		return Vec2i(x * s, y * s);
	}
	inline Vec2i Vec2i::operator/(int s) const noexcept {
		return Vec2i(x / s, y / s);
	}
	inline Vec2i& Vec2i::operator+=(int s) noexcept {
		x += s;
		y += s;
		return *this;
	}
	inline Vec2i& Vec2i::operator-=(int s) noexcept {
		x -= s;
		y -= s;
		return *this;
	}
	inline Vec2i& Vec2i::operator*=(int s) noexcept {
		x *= s;
		y *= s;
		return *this;
	}
	inline Vec2i& Vec2i::operator/=(int s) noexcept {
		x /= s;
		y /= s;
		return *this;
	}

	inline bool Vec2i::operator==(const Vec2i& vec) const noexcept {
		return x == vec.x && y == vec.y;
	}
	inline bool Vec2i::operator!=(const Vec2i& vec) const noexcept {
		return !(*this == vec);
	}

	inline Vec2i Vec2i::operator-() const noexcept {
		return Vec2i(-x, -y);
	}
}
