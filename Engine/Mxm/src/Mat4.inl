#undef near
#undef far

namespace Mxm
{
    constexpr Mat4::Mat4() noexcept : _m{ 0.0f } {}

    constexpr Mat4::Mat4(float a00, float a01, float a02, float a03,
        float a10, float a11, float a12, float a13,
        float a20, float a21, float a22, float a23,
        float a30, float a31, float a32, float a33) noexcept :
        _m{ {a00, a01, a02, a03},
             {a10, a11, a12, a13},
             {a20, a21, a22, a23},
             {a30, a31, a32, a33} } {
    }

    constexpr Mat4::Mat4(const Vec4& vec1, const Vec4& vec2, const Vec4& vec3, const Vec4& vec4) noexcept :
        _m{  {vec1.x, vec2.x, vec3.x, vec4.x},
             {vec1.y, vec2.y, vec3.y, vec4.y},
             {vec1.z, vec2.z, vec3.z, vec4.z},
             {vec1.w, vec2.w, vec3.w, vec4.w} } {
    }

    inline Vec4 Mat4::operator[](size_t index) const noexcept {
        if (index > 3) return Vec4();
        return Vec4(_m[index][0], _m[index][1], _m[index][2], _m[index][3]);
    }
    inline Vec4 Mat4::col(size_t index) const noexcept {
        if (index > 3) return Vec4();
        return Vec4(_m[0][index], _m[1][index], _m[2][index], _m[3][index]);
    }

    inline Mat4 Mat4::operator+(const Mat4& mat) const noexcept {
        return Mat4(_m[0][0] + mat._m[0][0], _m[0][1] + mat._m[0][1], _m[0][2] + mat._m[0][2], _m[0][3] + mat._m[0][3],
                    _m[1][0] + mat._m[1][0], _m[1][1] + mat._m[1][1], _m[1][2] + mat._m[1][2], _m[1][3] + mat._m[1][3],
                    _m[2][0] + mat._m[2][0], _m[2][1] + mat._m[2][1], _m[2][2] + mat._m[2][2], _m[2][3] + mat._m[2][3],
                    _m[3][0] + mat._m[3][0], _m[3][1] + mat._m[3][1], _m[3][2] + mat._m[3][2], _m[3][3] + mat._m[3][3]);
    }

    inline Mat4 Mat4::operator-(const Mat4& mat) const noexcept {
        return Mat4(_m[0][0] - mat._m[0][0], _m[0][1] - mat._m[0][1], _m[0][2] - mat._m[0][2], _m[0][3] - mat._m[0][3],
                    _m[1][0] - mat._m[1][0], _m[1][1] - mat._m[1][1], _m[1][2] - mat._m[1][2], _m[1][3] - mat._m[1][3],
                    _m[2][0] - mat._m[2][0], _m[2][1] - mat._m[2][1], _m[2][2] - mat._m[2][2], _m[2][3] - mat._m[2][3],
                    _m[3][0] - mat._m[3][0], _m[3][1] - mat._m[3][1], _m[3][2] - mat._m[3][2], _m[3][3] - mat._m[3][3]);
    }

    inline Mat4 Mat4::operator*(const Mat4& mat) const noexcept {
        Mat4 result;
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                for (size_t k = 0; k < 4; k++)
                    result._m[i][j] += _m[i][k] * mat._m[k][j];
        return result;
    }

    inline Mat4 Mat4::operator+(float s) const noexcept {
        Mat4 result;
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                result._m[i][j] = _m[i][j] + s;
        return result;
    }

    inline Mat4 Mat4::operator-(float s) const noexcept {
        Mat4 result;
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                result._m[i][j] = _m[i][j] - s;
        return result;
    }

    inline Mat4 Mat4::operator*(float s) const noexcept {
        Mat4 result;
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                result._m[i][j] = _m[i][j] * s;
        return result;
    }

    inline Vec4 Mat4::operator*(const Vec4& vec) const noexcept {
        return Vec4(_m[0][0] * vec.x + _m[0][1] * vec.y + _m[0][2] * vec.z + _m[0][3] * vec.w,
                    _m[1][0] * vec.x + _m[1][1] * vec.y + _m[1][2] * vec.z + _m[1][3] * vec.w,
                    _m[2][0] * vec.x + _m[2][1] * vec.y + _m[2][2] * vec.z + _m[2][3] * vec.w,
                    _m[3][0] * vec.x + _m[3][1] * vec.y + _m[3][2] * vec.z + _m[3][3] * vec.w);
    }

    inline Mat4& Mat4::operator+=(const Mat4& mat) noexcept {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                _m[i][j] += mat._m[i][j];
        return *this;
    }

    inline Mat4& Mat4::operator-=(const Mat4& mat) noexcept {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                _m[i][j] -= mat._m[i][j];
        return *this;
    }

    inline Mat4& Mat4::operator*=(const Mat4& mat) noexcept {
        *this = (*this) * mat;
        return *this;
    }

    inline Mat4& Mat4::operator+=(float s) noexcept {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                _m[i][j] += s;
        return *this;
    }

    inline Mat4& Mat4::operator-=(float s) noexcept {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                _m[i][j] -= s;
        return *this;
    }

    inline Mat4& Mat4::operator*=(float s) noexcept {
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                _m[i][j] *= s;
        return *this;
    }

    inline float Mat4::det() const noexcept {
        float det00 = _m[1][1] * (_m[2][2] * _m[3][3] - _m[2][3] * _m[3][2]) -
            _m[1][2] * (_m[2][1] * _m[3][3] - _m[2][3] * _m[3][1]) +
            _m[1][3] * (_m[2][1] * _m[3][2] - _m[2][2] * _m[3][1]);

        float det01 = _m[1][0] * (_m[2][2] * _m[3][3] - _m[2][3] * _m[3][2]) -
            _m[1][2] * (_m[2][0] * _m[3][3] - _m[2][3] * _m[3][0]) +
            _m[1][3] * (_m[2][0] * _m[3][2] - _m[2][2] * _m[3][0]);

        float det02 = _m[1][0] * (_m[2][1] * _m[3][3] - _m[2][3] * _m[3][1]) -
            _m[1][1] * (_m[2][0] * _m[3][3] - _m[2][3] * _m[3][0]) +
            _m[1][3] * (_m[2][0] * _m[3][1] - _m[2][1] * _m[3][0]);

        float det03 = _m[1][0] * (_m[2][1] * _m[3][2] - _m[2][2] * _m[3][1]) -
            _m[1][1] * (_m[2][0] * _m[3][2] - _m[2][2] * _m[3][0]) +
            _m[1][2] * (_m[2][0] * _m[3][1] - _m[2][1] * _m[3][0]);

        return _m[0][0] * det00 - _m[0][1] * det01 + _m[0][2] * det02 - _m[0][3] * det03;
    }
    inline Mat4 Mat4::transposed() const noexcept {
        Mat4 result;
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                result._m[i][j] = _m[j][i];
        return result;
    }
    inline Mat4 Mat4::abs() const noexcept {
        Mat4 result;
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                result._m[i][j] = fabsf(_m[i][j]);
        return result;
    }

    inline Mat4 Mat4::identity() noexcept {
        return Mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    inline Mat4 Mat4::scaling(float sx, float sy, float sz) noexcept {
        return Mat4(
            sx, 0.0f, 0.0f, 0.0f,
            0.0f, sy, 0.0f, 0.0f,
            0.0f, 0.0f, sz, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    inline Mat4 Mat4::scaling(const Vec3& sv) noexcept {
        return Mat4(
            sv.x, 0.0f, 0.0f, 0.0f,
            0.0f, sv.y, 0.0f, 0.0f,
            0.0f, 0.0f, sv.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    inline Mat4 Mat4::rotationX(float angle) noexcept {
        float rad = Mxm::Consts::DEG2RAD * angle;

        float cs = cosf(rad);
        float sn = sinf(rad);

        return Mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, cs, -sn, 0.0f,
            0.0f, sn, cs, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    inline Mat4 Mat4::rotationY(float angle) noexcept {
        float rad = Mxm::Consts::DEG2RAD * angle;

        float cs = cosf(rad);
        float sn = sinf(rad);

        return Mat4(
            cs, 0.0f, sn, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -sn, 0.0f, cs, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    inline Mat4 Mat4::rotationZ(float angle) noexcept {
        float rad = Mxm::Consts::DEG2RAD * angle;

        float cs = cosf(rad);
        float sn = sinf(rad);

        return Mat4(
            cs, -sn, 0.0f, 0.0f,
            sn, cs, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    inline Mat4 Mat4::rotation(const Quat& quat) noexcept {
        float w = quat.w, x = quat.x, y = quat.y, z = quat.z;

        float ww = w * w;
        float xy = x * y;
        float yz = y * z;
        float xz = x * z;

        float wx = w * x;
        float wy = w * y;
        float wz = w * z;

        return Mat4(
            2.0f * (ww + x*x) - 1.0f, 2.0f * (xy - wz),         2.0f * (xz + wy),         0.0f,
            2.0f * (xy + wz),         2.0f * (ww + y*y) - 1.0f, 2.0f * (yz - wx),         0.0f,
            2.0f * (xz - wy),         2.0f * (yz + wx),         2.0f * (ww + z*z) - 1.0f, 0.0f,
            0.0f,                     0.0f,                     0.0f,                     1.0f
        );
    }

    inline Mat4 Mat4::translation(float tx, float ty, float tz) noexcept {
        return Mat4(
            1.0f, 0.0f, 0.0f, tx,
            0.0f, 1.0f, 0.0f, ty,
            0.0f, 0.0f, 1.0f, tz,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }
    inline Mat4 Mat4::translation(const Vec3& tv) noexcept {
        return Mat4(
            1.0f, 0.0f, 0.0f, tv.x,
            0.0f, 1.0f, 0.0f, tv.y,
            0.0f, 0.0f, 1.0f, tv.z,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }
    inline Mat4 Mat4::perspective(float fov, float aspect, float near, float far) noexcept {
        float h = 1.0f / tanf(fov * Mxm::Consts::DEG2RAD / 2.0f);
        float zDist = far - near;
        return Mat4(
            h / aspect, 0, 0, 0,
            0, h, 0, 0,
            0, 0, far / zDist, -near * far / zDist,
            0, 0, 1, 0
        );
    }
    inline Mat4 Mat4::ortho(float r, float l, float t, float b, float n, float f) noexcept {
        return Mat4(
            2.0f / (r - l), 0, 0, (-r - l) / (r - l),
            0, 2.0f / (t - b), 0, (-t - b) / (t - b),
            0, 0, 2.0f / (f - n), (-f - n) / (f - n),
            0, 0, 0, 1.0f
        );
    }
    inline Mat4 Mat4::view(const Vec3& right, const Vec3& up, const Vec3& forward, const Vec3& pos) {
        return Mat4(
            right.x, right.y, right.z, -right.dot(pos),
            up.x, up.y, up.z, -up.dot(pos),
            forward.x, forward.y, forward.z, -forward.dot(pos),
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }
    inline Mat4 Mat4::view(const Vec3& forward, const Vec3& pos) {
        Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
        Vec3 right = up.cross(forward).normalized();
        up = forward.cross(right).normalized();
        return view(right, up, forward, pos);
    }
    inline Mat4 Mat4::screenSpace(int width, int height, int offsetX, int offsetY) noexcept {
        float halfWidth = static_cast<float>(width) / 2.0f;
        float halfHeight = static_cast<float>(height) / 2.0f;

        return Mat4(
            halfWidth, 0, 0, halfWidth + offsetX,
            0, -halfHeight, 0, halfHeight + offsetY,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }
}
