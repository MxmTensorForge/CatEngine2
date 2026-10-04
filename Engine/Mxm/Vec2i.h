#ifndef VEC2I_H
#define VEC2I_H

#include <cmath>
#include <cassert>
#include "Consts.h"

namespace Mxm
{
	struct Vec2i {
		int x, y;

		constexpr Vec2i() noexcept;
		constexpr explicit Vec2i(int s) noexcept;
		constexpr explicit Vec2i(int vx, int vy) noexcept;

		int& operator[](size_t index) noexcept;
		const int& operator[](size_t index) const noexcept;

		Vec2i operator+(const Vec2i& vec) const noexcept;
		Vec2i operator-(const Vec2i& vec) const noexcept;
		Vec2i operator*(const Vec2i& vec) const noexcept;
		Vec2i operator/(const Vec2i& vec) const noexcept;

		Vec2i& operator+=(const Vec2i& vec) noexcept;
		Vec2i& operator-=(const Vec2i& vec) noexcept;
		Vec2i& operator*=(const Vec2i& vec) noexcept;
		Vec2i& operator/=(const Vec2i& vec) noexcept;

		Vec2i operator+(int s) const noexcept;
		Vec2i operator-(int s) const noexcept;
		Vec2i operator*(int s) const noexcept;
		Vec2i operator/(int s) const noexcept;
		Vec2i& operator+=(int s) noexcept;
		Vec2i& operator-=(int s) noexcept;
		Vec2i& operator*=(int s) noexcept;
		Vec2i& operator/=(int s) noexcept;

		Vec2i operator-() const noexcept;

		bool operator==(const Vec2i& vec) const noexcept;
		bool operator!=(const Vec2i& vec) const noexcept;
	};
}

#include "src/Vec2i.inl"

#endif // !MXM_H
