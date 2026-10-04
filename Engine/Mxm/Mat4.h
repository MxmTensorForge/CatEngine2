#ifndef MAT4_H
#define MAT4_H

#include <cmath>
#include "Vec4.h"
#include "Quat.h"

namespace Mxm
{
    class Mat4 final
    {
    private:
        float _m[4][4];
    public:
        constexpr Mat4() noexcept;
        constexpr explicit Mat4(float a00, float a01, float a02, float a03,
             float a10, float a11, float a12, float a13,
             float a20, float a21, float a22, float a23,
             float a30, float a31, float a32, float a33) noexcept;
        constexpr explicit Mat4(const Vec4& vec1, const Vec4& vec2, const Vec4& vec3, const Vec4& vec4) noexcept;

        const float* data() const noexcept { return &(_m[0][0]); }

        Vec4 operator[](size_t index) const noexcept;
        Vec4 col(size_t index) const noexcept;

        Mat4 operator+(const Mat4& mat) const noexcept;
        Mat4 operator-(const Mat4& mat) const noexcept;
        Mat4 operator*(const Mat4& mat) const noexcept;

        Mat4 operator+(float s) const noexcept;
        Mat4 operator-(float s) const noexcept;
        Mat4 operator*(float s) const noexcept;

        Vec4 operator*(const Vec4& vec) const noexcept;

        Mat4& operator+=(const Mat4& mat) noexcept;
        Mat4& operator-=(const Mat4& mat) noexcept;
        Mat4& operator*=(const Mat4& mat) noexcept;

        Mat4& operator+=(float s) noexcept;
        Mat4& operator-=(float s) noexcept;
        Mat4& operator*=(float s) noexcept;

        float det() const noexcept;
        Mat4 transposed() const noexcept;
        Mat4 abs() const noexcept;

        static Mat4 identity() noexcept;
        static Mat4 scaling(float sx, float sy, float sz) noexcept;
        static Mat4 scaling(const Vec3& sv) noexcept;

        static Mat4 rotationX(float angle) noexcept;
        static Mat4 rotationY(float angle) noexcept;
        static Mat4 rotationZ(float angle) noexcept;

        static Mat4 rotation(const Quat& quat) noexcept;

        static Mat4 translation(float tx, float ty, float tz) noexcept;
        static Mat4 translation(const Vec3& tv) noexcept;
        static Mat4 perspective(float fov, float aspect, float near, float far) noexcept;
        static Mat4 ortho(float r, float l, float t, float b, float n, float f) noexcept;
        static Mat4 view(const Vec3& right, const Vec3& up, const Vec3& forward, const Vec3& pos);
        static Mat4 view(const Vec3& forward, const Vec3& pos);
        static Mat4 screenSpace(int width, int height, int offsetX = 0, int offsetY = 0) noexcept;
    };
}

#include "src/Mat4.inl"

#endif // !MAT4_H
