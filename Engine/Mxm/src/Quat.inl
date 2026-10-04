namespace Mxm
{
	constexpr Quat::Quat() noexcept : w{}, x{}, y{}, z{} {}
	constexpr Quat::Quat(float w, float x, float y, float z) noexcept 
		: w{w}, x{x}, y{y}, z{z} {}

	inline Quat Quat::operator*(const Quat& other) const noexcept {
		return Quat(
			w * other.w - x * other.x - y * other.y - z * other.z,
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y + x * other.z + y * other.w - z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w
		);
	}
	inline Quat Quat::operator+(const Quat& other) const noexcept {
		return Quat(
			w + other.w, x + other.x, y + other.y, z + other.z
		);
	}
	inline Quat Quat::operator-(const Quat& other) const noexcept {
		return Quat(
			w - other.w, x - other.x, y - other.y, z - other.z
		);
	}

	inline Quat& Quat::operator*=(const Quat& other) noexcept {
		*this = *this * other;
		return *this;
	}
	inline Quat& Quat::operator+=(const Quat& other) noexcept {
		*this = *this + other;
		return *this;
	}
	inline Quat& Quat::operator-=(const Quat& other) noexcept {
		*this = *this - other;
		return *this;
	}

	inline Quat Quat::operator*(float s) const noexcept {
		return Quat(
			w * s, x * s, y * s, z * s
		);
	}
	inline Quat Quat::operator/(float s) const noexcept {
		return Quat(
			w / s, x / s, y / s, z / s
		);
	}

	inline Quat& Quat::operator*=(float s) noexcept {
		*this = *this * s;
		return *this;
	}
	inline Quat& Quat::operator/=(float s) noexcept {
		*this = *this / s;
		return *this;
	}

	inline float Quat::length2() const noexcept {
		return w * w + x * x + y * y + z * z;
	}
	inline float Quat::length() const noexcept {
		return sqrtf(length2());
	}

	inline float Quat::dot(const Quat& other) const noexcept {
		return w * other.w + x * other.x + y * other.y + z * other.z;
	}

	inline Quat Quat::normalized() const noexcept {
		float len = length();
		if (len < Mxm::Consts::EPS) return Quat::identity();

		return *this / length();
	}

	inline Quat Quat::conjugated() const noexcept {
		return Quat(w, -x, -y, -z);
	}
	inline Quat Quat::inversed() const noexcept {
		return conjugated() / length2();
	}

	inline Mxm::Vec3 Quat::eulerAngles() const noexcept {
		float pitch = asinf(2.0f * (w * x - y * z)) * Mxm::Consts::RAD2DEG;

		float yaw = atan2f(2.0f * (x * z + w * y), 2.0f * (w * w + z * z) - 1.0f) * Mxm::Consts::RAD2DEG;

		float roll = atan2f(2.0f * (x * y + w * z), 2.0f * (w * w + y * y) - 1.0f) * Mxm::Consts::RAD2DEG;

		return Mxm::Vec3(pitch, yaw, roll);
	}
	inline void Quat::toAxisAngle(Mxm::Vec3& axis, float& angle) const noexcept {
		angle = Mxm::Consts::RAD2DEG * 2.0f * acosf(w);
		
		float s = sqrtf(1.0f - w*w);
		if (s < Mxm::Consts::EPS) {
			axis = Mxm::Vec3(1.0f, 0.0f, 0.0f);
		}
		else {
			axis.x = x / s;
			axis.y = y / s;
			axis.z = z / s;
		}
	}

	inline Quat Quat::euler(float pitch, float yaw, float roll) noexcept {
		float halfPitchRad = Mxm::Consts::DEG2RAD * pitch * 0.5f;
		float halfYawRad = Mxm::Consts::DEG2RAD * yaw * 0.5f;
		float halfRollRad = Mxm::Consts::DEG2RAD * roll * 0.5f;

		Quat qPitch = Quat(cosf(halfPitchRad), sinf(halfPitchRad), 0.0f, 0.0f);
		Quat qYaw = Quat(cosf(halfYawRad), 0.0f, sinf(halfYawRad), 0.0f);
		Quat qRoll = Quat(cosf(halfRollRad), 0.0f, 0.0f, sinf(halfRollRad));

		return (qYaw * qPitch * qRoll).normalized();
	}
	inline Quat Quat::euler(const Mxm::Vec3& angles) noexcept {
		return euler(angles.x, angles.y, angles.z);
	}

	inline Quat Quat::aroundAxis(const Mxm::Vec3& axis, float angle) noexcept {
		float halfAngleRad = Mxm::Consts::DEG2RAD * angle * 0.5f;

		float c = cosf(halfAngleRad), s = sinf(halfAngleRad);
		return Quat(c, s * axis.x, s * axis.y, s * axis.z);
	}

	inline Quat Quat::lookRotation(const Mxm::Vec3& forward) noexcept {
	    Mxm::Vec3 targetForward = forward.normalized();

		float yaw = atan2f(targetForward.x, targetForward.z);
		float pitch = -asinf(targetForward.y);

		return Mxm::Quat::euler(pitch * Mxm::Consts::RAD2DEG, yaw * Mxm::Consts::RAD2DEG, 0);
	}

	inline Quat Quat::slerp(const Quat& quat, float t) const noexcept {
		float angle = acosf((*this).dot(quat));
		float invSAngle = 1.0f / sinf(angle);

		return (*this) * sinf((1.0f - t) * angle) * invSAngle + quat * sinf(t * angle) * invSAngle;
	}
	inline Quat Quat::lerp(const Quat& quat, float t) const noexcept {
		return ((*this) * (1.0f - t) + quat * t);
	}

	inline Quat Quat::identity() noexcept {
		return Quat(1.0f, 0.0f, 0.0f, 0.0f);
	}
}
