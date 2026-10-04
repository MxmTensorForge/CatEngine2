#ifndef VEC3I_H
#define VEC3I_H

#include <cmath>
#include <cassert>
#include "Consts.h"

namespace Mxm
{
	struct Vec3i {
		int x, y, z;

		constexpr Vec3i() noexcept;
		constexpr explicit Vec3i(int s) noexcept;
		constexpr explicit Vec3i(int vx, int vy, int vz) noexcept;

		int& operator[](size_t index) noexcept;
		const int& operator[](size_t index) const noexcept;

		Vec3i operator+(const Vec3i& vec) const noexcept;
		Vec3i operator-(const Vec3i& vec) const noexcept;
		Vec3i operator*(const Vec3i& vec) const noexcept;
		Vec3i operator/(const Vec3i& vec) const noexcept;

		Vec3i& operator+=(const Vec3i& vec) noexcept;
		Vec3i& operator-=(const Vec3i& vec) noexcept;
		Vec3i& operator*=(const Vec3i& vec) noexcept;
		Vec3i& operator/=(const Vec3i& vec) noexcept;

		Vec3i operator+(int s) const noexcept;
		Vec3i operator-(int s) const noexcept;
		Vec3i operator*(int s) const noexcept;
		Vec3i operator/(int s) const noexcept;
		Vec3i& operator+=(int s) noexcept;
		Vec3i& operator-=(int s) noexcept;
		Vec3i& operator*=(int s) noexcept;
		Vec3i& operator/=(int s) noexcept;

		Vec3i operator-() const noexcept;

		bool operator==(const Vec3i& vec) const noexcept;
		bool operator!=(const Vec3i& vec) const noexcept;
	};
}

#include "src/Vec3i.inl"

#endif // !MXM_H
