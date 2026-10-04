namespace Mxm {
	////////////
	/// Vec3 ///
	////////////
	constexpr Vec3::Vec3() noexcept : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } {}
	constexpr Vec3::Vec3(float s) noexcept : x{ s }, y{ s }, z{ s } {}
	constexpr Vec3::Vec3(float vx, float vy, float vz) noexcept : x{ vx }, y{ vy }, z{ vz } {}
	constexpr Vec3::Vec3(const Vec2& vec, float vz) noexcept : x{ vec.x }, y{ vec.y }, z{ vz } {}

	inline float& Vec3::operator[](size_t index) noexcept {
		assert(index < 3);
		return (&x)[index];
	}
	inline const float& Vec3::operator[](size_t index) const noexcept {
		assert(index < 3);
		return (&x)[index];
	}

	inline Vec3 Vec3::operator+(const Vec3& vec) const noexcept {
		return Vec3(x + vec.x, y + vec.y, z + vec.z);
	}
	inline Vec3 Vec3::operator-(const Vec3& vec) const noexcept {
		return Vec3(x - vec.x, y - vec.y, z - vec.z);
	}
	inline Vec3 Vec3::operator*(const Vec3& vec) const noexcept {
		return Vec3(x * vec.x, y * vec.y, z * vec.z);
	}
	inline Vec3 Vec3::operator/(const Vec3& vec) const noexcept {
		return Vec3(x / vec.x, y / vec.y, z / vec.z);
	}
	inline Vec3& Vec3::operator+=(const Vec3& vec) noexcept {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	inline Vec3& Vec3::operator-=(const Vec3& vec) noexcept {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	inline Vec3& Vec3::operator*=(const Vec3& vec) noexcept {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}
	inline Vec3& Vec3::operator/=(const Vec3& vec) noexcept {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}

	inline Vec3 Vec3::operator+(float s) const noexcept {
		return Vec3(x + s, y + s, z + s);
	}
	inline Vec3 Vec3::operator-(float s) const noexcept {
		return Vec3(x - s, y - s, z - s);
	}
	inline Vec3 Vec3::operator*(float s) const noexcept {
		return Vec3(x * s, y * s, z * s);
	}
	inline Vec3 Vec3::operator/(float s) const noexcept {
		return Vec3(x / s, y / s, z / s);
	}
	inline Vec3& Vec3::operator+=(float s) noexcept {
		x += s;
		y += s;
		z += s;
		return *this;
	}
	inline Vec3& Vec3::operator-=(float s) noexcept {
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}
	inline Vec3& Vec3::operator*=(float s) noexcept {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline Vec3& Vec3::operator/=(float s) noexcept {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	inline bool Vec3::operator==(const Vec3& vec) const noexcept {
		return fabsf(x - vec.x) < Mxm::Consts::EPS &&
			fabsf(y - vec.y) < Mxm::Consts::EPS &&
			fabsf(z - vec.z) < Mxm::Consts::EPS;
	}
	inline bool Vec3::operator!=(const Vec3& vec) const noexcept {
		return !(*this == vec);
	}

	inline Vec2 Vec3::toVec2() const noexcept {
		return Vec2(this->x, this->y);
	}

	inline Vec3 Vec3::operator-() const noexcept {
		return Vec3(-x, -y, -z);
	}

	inline float Vec3::dot(const Vec3& vec) const noexcept {
		return x * vec.x + y * vec.y + z * vec.z;
	}
	inline float Vec3::length() const noexcept {
		return sqrtf(x * x + y * y + z * z);
	}
	inline float Vec3::length2() const noexcept {
		return x * x + y * y + z * z;
	}
	inline Vec3 Vec3::normalized() const noexcept {
		float len = length();
		if (len < Mxm::Consts::EPS) return Vec3();
		return *this / len;
	}
	inline Vec3 Vec3::cross(const Vec3& vec) const noexcept {
		return Vec3(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x
		);
	}
	inline Vec3 Vec3::abs() const noexcept {
		return Vec3(fabsf(x), fabsf(y), fabsf(z));
	}

	inline float Vec3::angleBetween(const Vec3& vec) const noexcept {
		float dotVal = dot(vec);
		float lenProduct = length() * vec.length();

		if (lenProduct < Consts::EPS) return 0.0f;

		dotVal /= lenProduct;
		dotVal = fmaxf(-1.0f, fminf(dotVal, 1.0f));
		return acosf(dotVal);
	}
	inline Vec3 Vec3::lerp(const Vec3& vec, float t) const noexcept {
		return *this + (vec - *this) * t;
	}
	inline Vec3 Vec3::slerp(const Vec3& vec, float t) const noexcept {
		float angle = angleBetween(vec);
		if (angle < Consts::EPS) return vec;

		float sn = sinf(angle);
		float w1 = sinf((1.0f - t) * angle) / sn;
		float w2 = sinf(t * angle) / sn;
		return *this * w1 + vec * w2;
	}
	
	inline Vec3 Vec3::i() noexcept {
	    return Vec3(1.0f, 0.0f, 0.0f);
	}
	inline Vec3 Vec3::j() noexcept {
	    return Vec3(0.0f, 1.0f, 0.0f);
	}
	inline Vec3 Vec3::k() noexcept {
	    return Vec3(0.0f, 0.0f, 1.0f);
	}
}
