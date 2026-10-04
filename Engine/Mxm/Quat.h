#ifndef QUAT_H
#define QUAT_H

#include <cmath>
#include "Vec3.h"

namespace Mxm
{
	struct Quat
	{
		float w, x, y, z;

		constexpr Quat() noexcept;
		constexpr Quat(float w, float x, float y, float z) noexcept;

		Quat operator*(const Quat& other) const noexcept;
		Quat operator+(const Quat& other) const noexcept;
		Quat operator-(const Quat& other) const noexcept;

		Quat& operator*=(const Quat& other) noexcept;
		Quat& operator+=(const Quat& other) noexcept;
		Quat& operator-=(const Quat& other) noexcept;

		Quat operator*(float s) const noexcept;
		Quat operator/(float s) const noexcept;

		Quat& operator*=(float s) noexcept;
		Quat& operator/=(float s) noexcept;

		float length2() const noexcept;
		float length() const noexcept;

		float dot(const Quat& other) const noexcept;

		Quat normalized() const noexcept;
		Quat conjugated() const noexcept;
		Quat inversed() const noexcept;

		Mxm::Vec3 eulerAngles() const noexcept;
		void toAxisAngle(Mxm::Vec3& axis, float& angle) const noexcept;

		static Quat euler(float pitch, float yaw, float roll) noexcept;
		static Quat euler(const Mxm::Vec3& angles) noexcept;
		static Quat aroundAxis(const Mxm::Vec3& axis, float angle) noexcept;

		static Quat lookRotation(const Mxm::Vec3& forward) noexcept;

		Quat slerp(const Quat& quat, float t) const noexcept;
		Quat lerp(const Quat& quat, float t) const noexcept;

		static Quat identity() noexcept;
	};
}

#include "src/Quat.inl"

#endif // !QUAT_H
