#ifndef MAT2_H
#define MAT2_H

#include <cmath>
#include "Vec2.h"

namespace Mxm
{
	class Mat2 final 
	{
	private:
		float _m[2][2];
	public:
		constexpr Mat2() noexcept;
		constexpr explicit Mat2(float a00, float a01, float a10, float a11) noexcept;
		constexpr explicit Mat2(const Vec2& vec1, const Vec2& vec2) noexcept;

		float* data() noexcept { return &(_m[0][0]); }

		Vec2 operator[](size_t index) const noexcept;
		Vec2 col(size_t index) const noexcept;

		Mat2 operator+(const Mat2& mat) const noexcept;
		Mat2 operator-(const Mat2& mat) const noexcept;
		Mat2 operator*(const Mat2& mat) const noexcept;

		Mat2 operator+(float s) const noexcept;
		Mat2 operator-(float s) const noexcept;
		Mat2 operator*(float s) const noexcept;

		Vec2 operator*(const Vec2& vec) const noexcept;

		Mat2& operator+=(const Mat2& mat) noexcept;
		Mat2& operator-=(const Mat2& mat) noexcept;
		Mat2& operator*=(const Mat2& mat) noexcept;

		Mat2& operator+=(float s) noexcept;
		Mat2& operator-=(float s) noexcept;
		Mat2& operator*=(float s) noexcept;

		float det() const noexcept;
		Mat2 transposed() const noexcept;
		Mat2 inversed() const noexcept;
		Mat2 abs() const noexcept;

		static Mat2 identiry() noexcept;
		static Mat2 scaling(float sx, float sy) noexcept;
		static Mat2 scaling(const Vec2& sv) noexcept;

		static Mat2 rotation(float angle) noexcept;
	};
}

#include "src/Mat2.inl"

#endif // !MXM_H
