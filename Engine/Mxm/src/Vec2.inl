namespace Mxm {
	////////////
	/// Vec2 ///
	////////////
	constexpr Vec2::Vec2() noexcept : x{ 0.0f }, y{ 0.0f } {}
	constexpr Vec2::Vec2(float s) noexcept : x{ s }, y{ s } {}
	constexpr Vec2::Vec2(float vx, float vy) noexcept : x{ vx }, y{ vy } {}

	inline float& Vec2::operator[](size_t index) noexcept {
		assert(index < 2);
		return (&x)[index];
	}
	inline const float& Vec2::operator[](size_t index) const noexcept {
		assert(index < 2);
		return (&x)[index];
	}

	inline Vec2 Vec2::operator+(const Vec2& vec) const noexcept {
		return Vec2(x + vec.x, y + vec.y);
	}
	inline Vec2 Vec2::operator-(const Vec2& vec) const noexcept {
		return Vec2(x - vec.x, y - vec.y);
	}
	inline Vec2 Vec2::operator*(const Vec2& vec) const noexcept {
		return Vec2(x * vec.x, y * vec.y);
	}
	inline Vec2 Vec2::operator/(const Vec2& vec) const noexcept {
		return Vec2(x / vec.x, y / vec.y);
	}
	inline Vec2& Vec2::operator+=(const Vec2& vec) noexcept {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	inline Vec2& Vec2::operator-=(const Vec2& vec) noexcept {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	inline Vec2& Vec2::operator*=(const Vec2& vec) noexcept {
		x *= vec.x;
		y *= vec.y;
		return *this;
	}
	inline Vec2& Vec2::operator/=(const Vec2& vec) noexcept {
		x /= vec.x;
		y /= vec.y;
		return *this;
	}

	inline Vec2 Vec2::operator+(float s) const noexcept {
		return Vec2(x + s, y + s);
	}
	inline Vec2 Vec2::operator-(float s) const noexcept {
		return Vec2(x - s, y - s);
	}
	inline Vec2 Vec2::operator*(float s) const noexcept {
		return Vec2(x * s, y * s);
	}
	inline Vec2 Vec2::operator/(float s) const noexcept {
		return Vec2(x / s, y / s);
	}
	inline Vec2& Vec2::operator+=(float s) noexcept {
		x += s;
		y += s;
		return *this;
	}
	inline Vec2& Vec2::operator-=(float s) noexcept {
		x -= s;
		y -= s;
		return *this;
	}
	inline Vec2& Vec2::operator*=(float s) noexcept {
		x *= s;
		y *= s;
		return *this;
	}
	inline Vec2& Vec2::operator/=(float s) noexcept {
		x /= s;
		y /= s;
		return *this;
	}

	inline bool Vec2::operator==(const Vec2& vec) const noexcept {
		return fabsf(x - vec.x) < Mxm::Consts::EPS &&
			fabsf(y - vec.y) < Mxm::Consts::EPS;
	}
	inline bool Vec2::operator!=(const Vec2& vec) const noexcept {
		return !(*this == vec);
	}

	inline Vec2 Vec2::operator-() const noexcept {
		return Vec2(-x, -y);
	}

	inline float Vec2::dot(const Vec2& vec) const noexcept {
		return x * vec.x + y * vec.y;
	}
	inline float Vec2::length() const noexcept {
		return sqrtf(x * x + y * y);
	}
	inline float Vec2::length2() const noexcept {
		return x * x + y * y;
	}
	inline Vec2 Vec2::normalized() const noexcept {
		float len = length();
		if (len < Mxm::Consts::EPS) return Vec2();
		return *this / len;
	}
	inline Vec2 Vec2::perp() const noexcept {
		return Vec2(-y, x);
	}
	inline Vec2 Vec2::abs() const noexcept {
		return Vec2(fabsf(x), fabsf(y));
	}

	inline float Vec2::angleBetween(const Vec2& vec) const noexcept {
		float dotVal = dot(vec);
		float lenProduct = length() * vec.length();

		if (lenProduct < Consts::EPS) return 0.0f;

		dotVal /= lenProduct;
		dotVal = fmaxf(-1.0f, fminf(dotVal, 1.0f));
		return acosf(dotVal);
	}
	inline Vec2 Vec2::lerp(const Vec2& vec, float t) const noexcept {
		return *this + (vec - *this) * t;
	}
	inline Vec2 Vec2::slerp(const Vec2& vec, float t) const noexcept {
		float angle = angleBetween(vec);
		if (angle < Consts::EPS) return vec;

		float sn = sinf(angle);
		float w1 = sinf((1.0f - t) * angle) / sn;
		float w2 = sinf(t * angle) / sn;
		return *this * w1 + vec * w2;
	}
	
	inline Vec2 Vec2::i() noexcept {
	    return Vec2(1.0f, 0.0f);
	}
	inline Vec2 Vec2::j() noexcept {
	    return Vec2(0.0f, 1.0f);
	}
}
