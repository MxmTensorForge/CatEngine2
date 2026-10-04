namespace Mxm {
	////////////
	/// Vec3i ///
	////////////
	constexpr Vec3i::Vec3i() noexcept : x{ 0 }, y{ 0 }, z{ 0 } {}
	constexpr Vec3i::Vec3i(int s) noexcept : x{ s }, y{ s } {}
	constexpr Vec3i::Vec3i(int vx, int vy, int vz) noexcept : x{ vx }, y{ vy }, z{ vz } {}

	inline int& Vec3i::operator[](size_t index) noexcept {
		assert(index < 3);
		return (&x)[index];
	}
	inline const int& Vec3i::operator[](size_t index) const noexcept {
		assert(index < 3);
		return (&x)[index];
	}

	inline Vec3i Vec3i::operator+(const Vec3i& vec) const noexcept {
		return Vec3i(x + vec.x, y + vec.y, z + vec.z);
	}
	inline Vec3i Vec3i::operator-(const Vec3i& vec) const noexcept {
		return Vec3i(x - vec.x, y - vec.y, z - vec.z);
	}
	inline Vec3i Vec3i::operator*(const Vec3i& vec) const noexcept {
		return Vec3i(x * vec.x, y * vec.y, z * vec.z);
	}
	inline Vec3i Vec3i::operator/(const Vec3i& vec) const noexcept {
		return Vec3i(x / vec.x, y / vec.y, z / vec.z);
	}
	inline Vec3i& Vec3i::operator+=(const Vec3i& vec) noexcept {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	inline Vec3i& Vec3i::operator-=(const Vec3i& vec) noexcept {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	inline Vec3i& Vec3i::operator*=(const Vec3i& vec) noexcept {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}
	inline Vec3i& Vec3i::operator/=(const Vec3i& vec) noexcept {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}

	inline Vec3i Vec3i::operator+(int s) const noexcept {
		return Vec3i(x + s, y + s, z + s);
	}
	inline Vec3i Vec3i::operator-(int s) const noexcept {
		return Vec3i(x - s, y - s, y - s);
	}
	inline Vec3i Vec3i::operator*(int s) const noexcept {
		return Vec3i(x * s, y * s, z * s);
	}
	inline Vec3i Vec3i::operator/(int s) const noexcept {
		return Vec3i(x / s, y / s, z / s);
	}
	inline Vec3i& Vec3i::operator+=(int s) noexcept {
		x += s;
		y += s;
		z += s;
		return *this;
	}
	inline Vec3i& Vec3i::operator-=(int s) noexcept {
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}
	inline Vec3i& Vec3i::operator*=(int s) noexcept {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline Vec3i& Vec3i::operator/=(int s) noexcept {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	inline bool Vec3i::operator==(const Vec3i& vec) const noexcept {
		return x == vec.x && y == vec.y && z == vec.z;
	}
	inline bool Vec3i::operator!=(const Vec3i& vec) const noexcept {
		return !(*this == vec);
	}

	inline Vec3i Vec3i::operator-() const noexcept {
		return Vec3i(-x, -y, -z);
	}
}
