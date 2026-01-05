#pragma once

namespace blaze {
    class Vec2 {
    public:
        float x;
        float y;

        // Constructors
        constexpr Vec2() : x(0.0f), y(0.0f) {}
        constexpr Vec2(int x, int y) : x((float)x), y((float)y) {}
        constexpr Vec2(float x, float y) : x(x), y(y) {}

        // Copy default
        constexpr Vec2(const Vec2&) = default;
        Vec2& operator=(const Vec2&) = default;

        // Arithmetic with another Vec2
        constexpr Vec2 operator+(const Vec2& rhs) const { return { x + rhs.x, y + rhs.y }; }
        constexpr Vec2 operator-(const Vec2& rhs) const { return { x - rhs.x, y - rhs.y }; }
        constexpr Vec2 operator*(const Vec2& rhs) const { return { x * rhs.x, y * rhs.y }; }
        constexpr Vec2 operator/(const Vec2& rhs) const { return { x / rhs.x, y / rhs.y }; }

        Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
        Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
        Vec2& operator*=(const Vec2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
        Vec2& operator/=(const Vec2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }

        // Arithmetic with a scalar
        constexpr Vec2 operator*(int s) const { return { x * s, y * s }; }
        constexpr Vec2 operator/(int s) const { return { x / s, y / s }; }

        Vec2& operator*=(int s) { x *= s; y *= s; return *this; }
        Vec2& operator/=(int s) { x /= s; y /= s; return *this; }

        // Comparison
        constexpr bool operator==(const Vec2& rhs) const { return x == rhs.x && y == rhs.y; }
        constexpr bool operator!=(const Vec2& rhs) const { return !(*this == rhs); }
    };

    // Allow scalar * Vec2
    inline constexpr Vec2 operator*(float s, const Vec2& v) {
        return { v.x * s, v.y * s };
    }
}