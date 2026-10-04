namespace Mxm
{
	constexpr Mat2::Mat2() noexcept : _m{ 0.0f } {}
	constexpr Mat2::Mat2(float a00, float a01, float a10, float a11) noexcept : _m{ {a00, a01}, {a10, a11} } {}
	constexpr Mat2::Mat2(const Vec2& vec1, const Vec2& vec2) noexcept : _m{ {vec1.x, vec2.x}, {vec1.y, vec2.y} } {}

	inline Vec2 Mat2::operator[](size_t index) const noexcept {
		if (index > 1) return Vec2();
		return Vec2(_m[index][0], _m[index][1]);
	}
	inline Vec2 Mat2::col(size_t index) const noexcept {
		if (index > 1) return Vec2();
		return Vec2(_m[0][index], _m[1][index]);
	}

	inline Mat2 Mat2::operator+(const Mat2& mat) const noexcept {
		return Mat2(_m[0][0] + mat._m[0][0], _m[0][1] + mat._m[0][1],
			        _m[1][0] + mat._m[1][0], _m[1][1] + mat._m[1][1]);
	}
	inline Mat2 Mat2::operator-(const Mat2& mat) const noexcept {
		return Mat2(_m[0][0] - mat._m[0][0], _m[0][1] - mat._m[0][1],
			        _m[1][0] - mat._m[1][0], _m[1][1] - mat._m[1][1]);
	}
	inline Mat2 Mat2::operator*(const Mat2& mat) const noexcept {
		Mat2 result;
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				for (size_t k = 0; k < 2; k++)
					result._m[i][j] += _m[i][k] * mat._m[k][j];
		return result;
	}

	inline Mat2 Mat2::operator+(float s) const noexcept {
		Mat2 result;
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				result._m[i][j] = _m[i][j] + s;
		return result;
	}
	inline Mat2 Mat2::operator-(float s) const noexcept {
		Mat2 result;
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				result._m[i][j] = _m[i][j] - s;
		return result;
	}
	inline Mat2 Mat2::operator*(float s) const noexcept {
		Mat2 result;
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				result._m[i][j] = _m[i][j] * s;
		return result;
	}

	inline Vec2 Mat2::operator*(const Vec2& vec) const noexcept {
		return Vec2(_m[0][0] * vec.x + _m[0][1] * vec.y,
			        _m[1][0] * vec.x + _m[1][1] * vec.y);
	}

	inline Mat2& Mat2::operator+=(const Mat2& mat) noexcept {
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				_m[i][j] += mat._m[i][j];
	}
	inline Mat2& Mat2::operator-=(const Mat2& mat) noexcept {
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				_m[i][j] -= mat._m[i][j];
	}
	inline Mat2& Mat2::operator*=(const Mat2& mat) noexcept {
		*this = (*this) * mat;
		return *this;
	}

	inline Mat2& Mat2::operator+=(float s) noexcept {
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				_m[i][j] += s;
	}
	inline Mat2& Mat2::operator-=(float s) noexcept {
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				_m[i][j] -= s;
	}
	inline Mat2& Mat2::operator*=(float s) noexcept {
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				_m[i][j] *= s;
	}

	inline float Mat2::det() const noexcept {
		float determinant = _m[0][0] * _m[1][1] - _m[0][1] * _m[1][0];
		return determinant;
	}
	inline Mat2 Mat2::transposed() const noexcept {
		Mat2 result;
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				result._m[i][j] = _m[j][i];
	}
	inline Mat2 Mat2::inversed() const noexcept {
		float determinant = det();
		if (fabsf(determinant) < Consts::EPS) return Mat2();

		float invDeterminant = 1.0f / determinant;
		return Mat2(
			_m[1][1] * invDeterminant, -_m[0][1] * invDeterminant,
			-_m[1][0] * invDeterminant, _m[0][0] * invDeterminant
		);
	}
	inline Mat2 Mat2::abs() const noexcept {
		Mat2 result;
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
				result._m[i][j] = fabsf(_m[i][j]);
		return result;
	}

	inline Mat2 Mat2::identiry() noexcept {
		return Mat2(
			1.0f, 0.0f,
			0.0f, 1.0f
		);
	}
	inline Mat2 Mat2::scaling(float sx, float sy) noexcept {
		return Mat2(
			sx, 0.0f,
			0.0f, sy
		);
	}
	inline Mat2 Mat2::scaling(const Vec2& sv) noexcept {
		return Mat2(
			sv.x, 0.0f,
			0.0f, sv.y
		);
	}
	inline Mat2 Mat2::rotation(float angle) noexcept {
		float rad = Mxm::Consts::DEG2RAD * angle;

		float cs = cosf(rad);
		float sn = sinf(rad);

		return Mat2(
			cs, -sn,
			sn, cs
		);
	}
}
