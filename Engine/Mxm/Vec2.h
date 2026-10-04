#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <cassert>
#include "Consts.h"

namespace Mxm
{
	struct Vec2 {
		float x, y;

		constexpr Vec2() noexcept;
		constexpr explicit Vec2(float s) noexcept;
		constexpr explicit Vec2(float vx, float vy) noexcept;

		float& operator[](size_t index) noexcept;
		const float& operator[](size_t index) const noexcept;

		Vec2 operator+(const Vec2& vec) const noexcept;
		Vec2 operator-(const Vec2& vec) const noexcept;
		Vec2 operator*(const Vec2& vec) const noexcept;
		Vec2 operator/(const Vec2& vec) const noexcept;

		Vec2& operator+=(const Vec2& vec) noexcept;
		Vec2& operator-=(const Vec2& vec) noexcept;
		Vec2& operator*=(const Vec2& vec) noexcept;
		Vec2& operator/=(const Vec2& vec) noexcept;

		Vec2 operator+(float s) const noexcept;
		Vec2 operator-(float s) const noexcept;
		Vec2 operator*(float s) const noexcept;
		Vec2 operator/(float s) const noexcept;
		Vec2& operator+=(float s) noexcept;
		Vec2& operator-=(float s) noexcept;
		Vec2& operator*=(float s) noexcept;
		Vec2& operator/=(float s) noexcept;

		Vec2 operator-() const noexcept;

		bool operator==(const Vec2& vec) const noexcept;
		bool operator!=(const Vec2& vec) const noexcept;

		float dot(const Vec2& vec) const noexcept;
		float length() const noexcept;
		float length2() const noexcept;

		Vec2 normalized() const noexcept;
		Vec2 perp() const noexcept;
		Vec2 abs() const noexcept;

		float angleBetween(const Vec2& vec) const noexcept;
		Vec2 lerp(const Vec2& vec, float t) const noexcept;
		Vec2 slerp(const Vec2& vec, float t) const noexcept;
		
		static Vec2 i() noexcept;
		static Vec2 j() noexcept;
	};
}

#include "src/Vec2.inl"

#endif // !MXM_H
