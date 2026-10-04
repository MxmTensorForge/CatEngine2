#ifndef MAT3_H
#define MAT3_H

#include <cmath>
#include "Vec3.h"
#include "Quat.h"

namespace Mxm
{
    class Mat3 final
    {
    private:
        float _m[3][3];
    public:
        constexpr Mat3() noexcept;
        constexpr explicit Mat3(float a00, float a01, float a02,
            float a10, float a11, float a12,
            float a20, float a21, float a22) noexcept;
        constexpr explicit Mat3(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3) noexcept;

        float* data() noexcept { return &(_m[0][0]); }

        Vec3 operator[](size_t index) const noexcept;
        Vec3 col(size_t index) const noexcept;

        Mat3 operator+(const Mat3& mat) const noexcept;
        Mat3 operator-(const Mat3& mat) const noexcept;
        Mat3 operator*(const Mat3& mat) const noexcept;

        Mat3 operator+(float s) const noexcept;
        Mat3 operator-(float s) const noexcept;
        Mat3 operator*(float s) const noexcept;

        Vec3 operator*(const Vec3& vec) const noexcept;

        Mat3& operator+=(const Mat3& mat) noexcept;
        Mat3& operator-=(const Mat3& mat) noexcept;
        Mat3& operator*=(const Mat3& mat) noexcept;

        Mat3& operator+=(float s) noexcept;
        Mat3& operator-=(float s) noexcept;
        Mat3& operator*=(float s) noexcept;

        float det() const noexcept;
        Mat3 transposed() const noexcept;
        Mat3 inversed() const noexcept;
        Mat3 abs() const noexcept;

        static Mat3 identity() noexcept;
        static Mat3 scaling(float sx, float sy, float sz) noexcept;
        static Mat3 scaling(const Vec3& sv) noexcept;

        static Mat3 rotationX(float angle) noexcept;
        static Mat3 rotationY(float angle) noexcept;
        static Mat3 rotationZ(float angle) noexcept;

        static Mat3 rotation(const Quat& quat) noexcept;

        static Mat3 translation(float tx, float ty) noexcept;
        static Mat3 translation(const Vec2& tv) noexcept;
    };
}

#include "src/Mat3.inl"

#endif // !MAT3_H
