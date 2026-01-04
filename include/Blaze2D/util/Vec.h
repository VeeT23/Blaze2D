#pragma once

namespace Blaze {
    class Vec2 {
    public:
        int x;
        int y;

        // Constructors
        constexpr Vec2() : x(0), y(0) {}
        constexpr Vec2(int x, int y) : x(x), y(y) {}
        constexpr Vec2(float x, float y) : x((int)x), y((int)y) {}

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
    inline constexpr Vec2 operator*(int s, const Vec2& v) {
        return { v.x * s, v.y * s };
    }
}