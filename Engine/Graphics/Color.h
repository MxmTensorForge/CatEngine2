#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <cmath>

class Color final
{
private:
	uint32_t _argb; // 0xAARRGGBB
public:
    static constexpr uint8_t clamp(int value) noexcept {
        return static_cast<uint8_t>(value < 0 ? 0 : (value > 255 ? 255 : value));
    }

	constexpr Color() : _argb(0xFF000000) {}
	constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
		: _argb((a << 24) | (r << 16) | (g << 8) | b) {}

	constexpr explicit Color(uint32_t argb) : _argb(argb) {}

    constexpr uint8_t a() const noexcept { return (_argb >> 24) & 0xFF; }
	constexpr uint8_t r() const noexcept { return (_argb >> 16) & 0xFF; }
	constexpr uint8_t g() const noexcept { return (_argb >> 8) & 0xFF; }
	constexpr uint8_t b() const noexcept { return (_argb) & 0xFF; }

	constexpr uint32_t argb() const noexcept { return _argb; }

	void setR(uint8_t r) noexcept { _argb = (_argb & 0xFF00FFFF) | (r << 16); }
	void setG(uint8_t g) noexcept { _argb = (_argb & 0xFFFF00FF) | (g << 8); }
	void setB(uint8_t b) noexcept { _argb = (_argb & 0xFFFFFF00) | (b); }
	void setA(uint8_t a) noexcept { _argb = (_argb & 0x00FFFFFF) | (a << 24); }

	float rf() const noexcept { return r() / 255.0f; }
	float gf() const noexcept { return g() / 255.0f; }
	float bf() const noexcept { return b() / 255.0f; }
	float af() const noexcept { return a() / 255.0f; }

    Color operator*(float f) const noexcept {
        return Color(
            clamp(static_cast<int>(r() * f)),
            clamp(static_cast<int>(g() * f)),
            clamp(static_cast<int>(b() * f)),
            clamp(static_cast<int>(a() * f))
        );
    }
    Color& operator*=(float f) noexcept {
        *this = *this * f;
        return *this;
    }

    Color operator+(float f) const noexcept {
        return Color(
            clamp(static_cast<int>(r() + f)),
            clamp(static_cast<int>(g() + f)),
            clamp(static_cast<int>(b() + f)),
            clamp(static_cast<int>(a() + f))
        );
    }
    Color& operator+=(float f) noexcept {
        *this = *this + f;
        return *this;
    }

    Color operator-(float f) const noexcept {
        return Color(
            clamp(static_cast<int>(r() - f)),
            clamp(static_cast<int>(g() - f)),
            clamp(static_cast<int>(b() - f)),
            clamp(static_cast<int>(a() - f))
        );
    }
    Color& operator-=(float f) noexcept {
        *this = *this - f;
        return *this;
    }

    Color operator*(const Color& other) const noexcept {
        return Color(
            clamp(static_cast<int>(r() * other.rf())),
            clamp(static_cast<int>(g() * other.gf())),
            clamp(static_cast<int>(b() * other.bf())),
            clamp(static_cast<int>(a() * other.af()))
        );
    }
    Color& operator*=(const Color& other) noexcept {
        *this = *this * other;
        return *this;
    }

    Color operator+(const Color& other) const noexcept {
        return Color(
            clamp(static_cast<int>(r() + other.r())),
            clamp(static_cast<int>(g() + other.g())),
            clamp(static_cast<int>(b() + other.b())),
            clamp(static_cast<int>(a() + other.a()))
        );
    }
    Color& operator+=(const Color& other) noexcept {
        *this = *this + other;
        return *this;
    }

    Color operator-(const Color& other) const noexcept {
        return Color(
            clamp(static_cast<int>(r() - other.r())),
            clamp(static_cast<int>(g() - other.g())),
            clamp(static_cast<int>(b() - other.b())),
            clamp(static_cast<int>(a() - other.a()))
        );
    }
    Color& operator-=(const Color& other) noexcept {
        *this = *this - other;
        return *this;
    }

    bool operator==(const Color& other) const noexcept { return _argb == other._argb; }
    bool operator!=(const Color& other) const noexcept { return _argb != other._argb; }
};

#endif // !COLOR_H
