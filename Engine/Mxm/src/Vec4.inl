namespace Mxm {
	////////////
    /// Vec4 ///
    ////////////
	constexpr Vec4::Vec4() noexcept : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, w{ 0.0f } {}
	constexpr Vec4::Vec4(float s) noexcept : x{ s }, y{ s }, z{ s }, w{ s } {}
	constexpr Vec4::Vec4(float vx, float vy, float vz, float vw) noexcept : x{ vx }, y{ vy }, z{ vz }, w{ vw } {}
	constexpr Vec4::Vec4(const Vec2& vec, float vz, float vw) noexcept : x{ vec.x }, y{ vec.y }, z{ vz }, w{ vw } {}
	constexpr Vec4::Vec4(const Vec3& vec, float vw) noexcept : x{ vec.x }, y{ vec.y }, z{ vec.z }, w{ vw } {}

	inline float& Vec4::operator[](size_t index) noexcept {
		assert(index < 4);
		return (&x)[index];
	}
	inline const float& Vec4::operator[](size_t index) const noexcept {
		assert(index < 4);
		return (&x)[index];
	}

	inline Vec4 Vec4::operator+(const Vec4& vec) const noexcept {
		return Vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}
	inline Vec4 Vec4::operator-(const Vec4& vec) const noexcept {
		return Vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}
	inline Vec4 Vec4::operator*(const Vec4& vec) const noexcept {
		return Vec4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
	}
	inline Vec4 Vec4::operator/(const Vec4& vec) const noexcept {
		return Vec4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
	}
	inline Vec4& Vec4::operator+=(const Vec4& vec) noexcept {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}
	inline Vec4& Vec4::operator-=(const Vec4& vec) noexcept {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}
	inline Vec4& Vec4::operator*=(const Vec4& vec) noexcept {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		w *= vec.w;
		return *this;
	}
	inline Vec4& Vec4::operator/=(const Vec4& vec) noexcept {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		w /= vec.w;
		return *this;
	}

	inline Vec4 Vec4::operator+(float s) const noexcept {
		return Vec4(x + s, y + s, z + s, w + s);
	}
	inline Vec4 Vec4::operator-(float s) const noexcept {
		return Vec4(x - s, y - s, z - s, w - s);
	}
	inline Vec4 Vec4::operator*(float s) const noexcept {
		return Vec4(x * s, y * s, z * s, w * s);
	}
	inline Vec4 Vec4::operator/(float s) const noexcept {
		return Vec4(x / s, y / s, z / s, w / s);
	}
	inline Vec4& Vec4::operator+=(float s) noexcept {
		x += s;
		y += s;
		z += s;
		w += s;
		return *this;
	}
	inline Vec4& Vec4::operator-=(float s) noexcept {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
		return *this;
	}
	inline Vec4& Vec4::operator*=(float s) noexcept {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	inline Vec4& Vec4::operator/=(float s) noexcept {
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}

	inline bool Vec4::operator==(const Vec4& vec) const noexcept {
		return fabsf(x - vec.x) < Mxm::Consts::EPS &&
			fabsf(y - vec.y) < Mxm::Consts::EPS &&
			fabsf(z - vec.z) < Mxm::Consts::EPS &&
			fabsf(w - vec.w) < Mxm::Consts::EPS;
	}
	inline bool Vec4::operator!=(const Vec4& vec) const noexcept {
		return !(*this == vec);
	}

	inline Vec4 Vec4::operator-() const noexcept {
		return Vec4(-x, -y, -z, -w);
	}

	inline Vec3 Vec4::toVec3() const noexcept {
		return Vec3(this->x, this->y, this->z);
	}
	inline Vec2 Vec4::toVec2() const noexcept {
		return Vec2(this->x, this->y);
	}

	inline float Vec4::dot(const Vec4& vec) const noexcept {
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}
	inline float Vec4::length() const noexcept {
		return sqrtf(x * x + y * y + z * z + w * w);
	}
	inline Vec4 Vec4::normalized() const noexcept {
		float len = length();
		if (len < Mxm::Consts::EPS) return Vec4();
		return *this / len;
	}
	inline Vec4 Vec4::abs() const noexcept {
		return Vec4(fabsf(x), fabsf(y), fabsf(z), fabsf(w));
	}

	inline Vec4 Vec4::lerp(const Vec4& vec, float t) const noexcept {
		return *this + (vec - *this) * t;
	}
}
