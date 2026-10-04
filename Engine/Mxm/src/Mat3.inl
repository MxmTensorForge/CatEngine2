namespace Mxm
{
    constexpr Mat3::Mat3() noexcept : _m{ 0.0f } {}

    constexpr Mat3::Mat3(float a00, float a01, float a02,
                      float a10, float a11, float a12,
                      float a20, float a21, float a22) noexcept :
        _m{ {a00, a01, a02}, {a10, a11, a12}, {a20, a21, a22} } {
    }

    constexpr Mat3::Mat3(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3) noexcept :
        _m{ {vec1.x, vec2.x, vec3.x}, {vec1.y, vec2.y, vec3.y}, {vec1.z, vec2.z, vec3.z} } {
    }

    inline Vec3 Mat3::operator[](size_t index) const noexcept {
        if (index > 2) return Vec3();
        return Vec3(_m[index][0], _m[index][1], _m[index][2]);
    }
    inline Vec3 Mat3::col(size_t index) const noexcept {
        if (index > 2) return Vec3();
        return Vec3(_m[0][index], _m[1][index], _m[2][index]);
    }

    inline Mat3 Mat3::operator+(const Mat3& mat) const noexcept {
        return Mat3(_m[0][0] + mat._m[0][0], _m[0][1] + mat._m[0][1], _m[0][2] + mat._m[0][2],
                    _m[1][0] + mat._m[1][0], _m[1][1] + mat._m[1][1], _m[1][2] + mat._m[1][2],
                    _m[2][0] + mat._m[2][0], _m[2][1] + mat._m[2][1], _m[2][2] + mat._m[2][2]);
    }

    inline Mat3 Mat3::operator-(const Mat3& mat) const noexcept {
        return Mat3(_m[0][0] - mat._m[0][0], _m[0][1] - mat._m[0][1], _m[0][2] - mat._m[0][2],
                    _m[1][0] - mat._m[1][0], _m[1][1] - mat._m[1][1], _m[1][2] - mat._m[1][2],
                    _m[2][0] - mat._m[2][0], _m[2][1] - mat._m[2][1], _m[2][2] - mat._m[2][2]);
    }

    inline Mat3 Mat3::operator*(const Mat3& mat) const noexcept {
        Mat3 result;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                for (size_t k = 0; k < 3; k++)
                    result._m[i][j] += _m[i][k] * mat._m[k][j];
        return result;
    }

    inline Mat3 Mat3::operator+(float s) const noexcept {
        Mat3 result;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                result._m[i][j] = _m[i][j] + s;
        return result;
    }

    inline Mat3 Mat3::operator-(float s) const noexcept {
        Mat3 result;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                result._m[i][j] = _m[i][j] - s;
        return result;
    }

    inline Mat3 Mat3::operator*(float s) const noexcept {
        Mat3 result;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                result._m[i][j] = _m[i][j] * s;
        return result;
    }

    inline Vec3 Mat3::operator*(const Vec3& vec) const noexcept {
        return Vec3(_m[0][0] * vec.x + _m[0][1] * vec.y + _m[0][2] * vec.z,
                    _m[1][0] * vec.x + _m[1][1] * vec.y + _m[1][2] * vec.z,
                    _m[2][0] * vec.x + _m[2][1] * vec.y + _m[2][2] * vec.z);
    }

    inline Mat3& Mat3::operator+=(const Mat3& mat) noexcept {
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                _m[i][j] += mat._m[i][j];
        return *this;
    }

    inline Mat3& Mat3::operator-=(const Mat3& mat) noexcept {
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                _m[i][j] -= mat._m[i][j];
        return *this;
    }

    inline Mat3& Mat3::operator*=(const Mat3& mat) noexcept {
        *this = (*this) * mat;
        return *this;
    }

    inline Mat3& Mat3::operator+=(float s) noexcept {
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                _m[i][j] += s;
        return *this;
    }

    inline Mat3& Mat3::operator-=(float s) noexcept {
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                _m[i][j] -= s;
        return *this;
    }

    inline Mat3& Mat3::operator*=(float s) noexcept {
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                _m[i][j] *= s;
        return *this;
    }

    inline float Mat3::det() const noexcept {
        return _m[0][0] * (_m[1][1] * _m[2][2] - _m[1][2] * _m[2][1])
             - _m[0][1] * (_m[1][0] * _m[2][2] - _m[1][2] * _m[2][0])
             + _m[0][2] * (_m[1][0] * _m[2][1] - _m[1][1] * _m[2][0]);
    }

    inline Mat3 Mat3::transposed() const noexcept {
        Mat3 result;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                result._m[i][j] = _m[j][i];
        return result;
    }

    inline Mat3 Mat3::inversed() const noexcept {
        float determinant = det();
        if (fabsf(determinant) < Consts::EPS) return Mat3::identity();

        float invDeterminant = 1.0f / determinant;

        Mat3 c = Mat3(
            (_m[1][1] * _m[2][2] - _m[1][2] * _m[2][1]) * invDeterminant, -(_m[1][0] * _m[2][2] - _m[1][2] * _m[2][0]) * invDeterminant, (_m[1][0] * _m[2][1] - _m[1][1] * _m[2][0]) * invDeterminant,
            -(_m[0][1] * _m[2][2] - _m[0][2] * _m[2][1]) * invDeterminant, (_m[0][0] * _m[2][2] - _m[0][2] * _m[2][0]) * invDeterminant, -(_m[0][0] * _m[2][1] - _m[0][1] * _m[2][0]) * invDeterminant,
            (_m[0][1] * _m[1][2] - _m[0][2] * _m[1][1]) * invDeterminant, -(_m[0][0] * _m[1][2] - _m[0][2] * _m[1][0]) * invDeterminant, (_m[0][0] * _m[1][1] - _m[0][1] * _m[1][0]) * invDeterminant
        );

        return c.transposed();
    }
    inline Mat3 Mat3::abs() const noexcept {
        Mat3 result;
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                result._m[i][j] = fabsf(_m[i][j]);
        return result;
    }

    inline Mat3 Mat3::identity() noexcept {
        return Mat3(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        );
    }

    inline Mat3 Mat3::scaling(float sx, float sy, float sz) noexcept {
        return Mat3(
            sx, 0.0f, 0.0f,
            0.0f, sy, 0.0f,
            0.0f, 0.0f, sz
        );
    }

    inline Mat3 Mat3::scaling(const Vec3& sv) noexcept {
        return Mat3(
            sv.x, 0.0f, 0.0f,
            0.0f, sv.y, 0.0f,
            0.0f, 0.0f, sv.z
        );
    }

    inline Mat3 Mat3::rotationX(float angle) noexcept {
        float rad = Mxm::Consts::DEG2RAD * angle;

        float cs = cosf(rad);
        float sn = sinf(rad);

        return Mat3(
            1.0f, 0.0f, 0.0f,
            0.0f, cs, -sn,
            0.0f, sn, cs
        );
    }

    inline Mat3 Mat3::rotationY(float angle) noexcept {
        float rad = Mxm::Consts::DEG2RAD * angle;

        float cs = cosf(rad);
        float sn = sinf(rad);

        return Mat3(
            cs, 0.0f, sn,
            0.0f, 1.0f, 0.0f,
            -sn, 0.0f, cs
        );
    }

    inline Mat3 Mat3::rotationZ(float angle) noexcept {
        float rad = Mxm::Consts::DEG2RAD * angle;

        float cs = cosf(rad);
        float sn = sinf(rad);

        return Mat3(
            cs, -sn, 0.0f,
            sn, cs, 0.0f,
            0.0f, 0.0f, 1.0f
        );
    }

    inline Mat3 Mat3::rotation(const Quat& quat) noexcept {
        float w = quat.w, x = quat.x, y = quat.y, z = quat.z;

        float ww = w * w;
        float xy = x * y;
        float yz = y * z;
        float xz = x * z;

        float wx = w * x;
        float wy = w * y;
        float wz = w * z;

        return Mat3(
            2.0f * (ww + x * x) - 1.0f, 2.0f * (xy - wz), 2.0f * (xz + wy),
            2.0f * (xy + wz), 2.0f * (ww + y * y) - 1.0f, 2.0f * (yz - wx),
            2.0f * (xz - wy), 2.0f * (yz + wx), 2.0f * (ww + z * z) - 1.0f
        );
    }

    inline Mat3 Mat3::translation(float tx, float ty) noexcept {
        return Mat3(
            1.0f, 0.0f, tx,
            0.0f, 1.0f, ty,
            0.0f, 0.0f, 1.0f
        );
    }
    inline Mat3 Mat3::translation(const Vec2& tv) noexcept {
        return Mat3(
            1.0f, 0.0f, tv.x,
            0.0f, 1.0f, tv.y,
            0.0f, 0.0f, 1.0f
        );
    }
}
