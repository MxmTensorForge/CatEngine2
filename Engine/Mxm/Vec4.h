#ifndef VEC4_H
#define VEC4_H

#include <cmath>

#include "Vec3.h"
#include "Consts.h"

namespace Mxm
{
	struct Vec4 {
		float x, y, z, w;

		constexpr Vec4() noexcept;
		constexpr explicit Vec4(float s) noexcept;
		constexpr explicit Vec4(float vx, float vy, float vz, float vw) noexcept;
		constexpr explicit Vec4(const Vec2& vec, float vz, float vw) noexcept;
		constexpr explicit Vec4(const Vec3& vec, float vw) noexcept;

		float& operator[](size_t index) noexcept;
		const float& operator[](size_t index) const noexcept;

		Vec4 operator+(const Vec4& vec) const noexcept;
		Vec4 operator-(const Vec4& vec) const noexcept;
		Vec4 operator*(const Vec4& vec) const noexcept;
		Vec4 operator/(const Vec4& vec) const noexcept;

		Vec4& operator+=(const Vec4& vec) noexcept;
		Vec4& operator-=(const Vec4& vec) noexcept;
		Vec4& operator*=(const Vec4& vec) noexcept;
		Vec4& operator/=(const Vec4& vec) noexcept;

		Vec4 operator+(float s) const noexcept;
		Vec4 operator-(float s) const noexcept;
		Vec4 operator*(float s) const noexcept;
		Vec4 operator/(float s) const noexcept;
		Vec4& operator+=(float s) noexcept;
		Vec4& operator-=(float s) noexcept;
		Vec4& operator*=(float s) noexcept;
		Vec4& operator/=(float s) noexcept;

		Vec4 operator-() const noexcept;

		bool operator==(const Vec4& vec) const noexcept;
		bool operator!=(const Vec4& vec) const noexcept;

		Vec3 toVec3() const noexcept;
		Vec2 toVec2() const noexcept;

		float dot(const Vec4& vec) const noexcept;
		float length() const noexcept;
		Vec4 normalized() const noexcept;
		Vec4 abs() const noexcept;

		Vec4 lerp(const Vec4& vec, float t) const noexcept;
	};
}

#include "src/Vec4.inl"

#endif // !MXM_H
