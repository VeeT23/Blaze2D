#pragma once
#include "Blaze2D/util/Vec.h"
#include <algorithm>

namespace blaze
{
    struct Rect {
        float x = 0.0f;
        float y = 0.0f;
        float w = 0.0f;
        float h = 0.0f;

        /* =========================
           Constructors
           ========================= */

        constexpr Rect() = default;

        // Position + size
        constexpr Rect(float x_, float y_, float w_, float h_)
            : x(x_), y(y_), w(w_), h(h_) {
        }

        // From position and size vectors
        constexpr Rect(const Vec2& pos, const Vec2& size)
            : x(pos.x), y(pos.y), w(size.x), h(size.y) {
        }

        // Point-to-point constructor (auto-normalized)
        static Rect fromPoints(const Vec2& a, const Vec2& b) {
            float minX = std::min(a.x, b.x);
            float minY = std::min(a.y, b.y);
            float maxX = std::max(a.x, b.x);
            float maxY = std::max(a.y, b.y);
            return Rect(minX, minY, maxX - minX, maxY - minY);
        }

        /* =========================
           Basic accessors
           ========================= */

        constexpr float left()   const { return x; }
        constexpr float right()  const { return x + w; }
        constexpr float top()    const { return y; }
        constexpr float bottom() const { return y + h; }

        constexpr Vec2 position() const { return { x, y }; }
        constexpr Vec2 size()     const { return { w, h }; }
        constexpr Vec2 center()   const { return { x + w * 0.5f, y + h * 0.5f }; }

        /* =========================
           State checks
           ========================= */

        constexpr bool empty() const {
            return w <= 0.0f || h <= 0.0f;
        }

        constexpr bool valid() const {
            return w >= 0.0f && h >= 0.0f;
        }

        /* =========================
           Normalization
           ========================= */

           // Ensures width/height are positive
        void normalize() {
            if (w < 0.0f) { x += w; w = -w; }
            if (h < 0.0f) { y += h; h = -h; }
        }

        Rect normalized() const {
            Rect r = *this;
            r.normalize();
            return r;
        }

        /* =========================
           Containment
           ========================= */

        constexpr bool contains(float px, float py) const {
            return px >= left() && px < right() &&
                py >= top() && py < bottom();
        }

        constexpr bool contains(const Vec2& p) const {
            return contains(p.x, p.y);
        }

        constexpr bool contains(const Rect& other) const {
            return other.left() >= left() &&
                other.right() <= right() &&
                other.top() >= top() &&
                other.bottom() <= bottom();
        }

        /* =========================
           Intersection
           ========================= */

        constexpr bool intersects(const Rect& other) const {
            return !(other.left() >= right() ||
                other.right() <= left() ||
                other.top() >= bottom() ||
                other.bottom() <= top());
        }

        Rect intersection(const Rect& other) const {
            float nx = std::max(left(), other.left());
            float ny = std::max(top(), other.top());
            float nr = std::min(right(), other.right());
            float nb = std::min(bottom(), other.bottom());

            if (nr <= nx || nb <= ny)
                return Rect();

            return Rect(nx, ny, nr - nx, nb - ny);
        }

        /* =========================
           Union / expansion
           ========================= */

        Rect united(const Rect& other) const {
            float nx = std::min(left(), other.left());
            float ny = std::min(top(), other.top());
            float nr = std::max(right(), other.right());
            float nb = std::max(bottom(), other.bottom());
            return Rect(nx, ny, nr - nx, nb - ny);
        }

        void expand(float amount) {
            x -= amount;
            y -= amount;
            w += amount * 2.0f;
            h += amount * 2.0f;
        }

        /* =========================
           Translation
           ========================= */

        constexpr Rect translated(float dx, float dy) const {
            return Rect(x + dx, y + dy, w, h);
        }

        constexpr Rect translated(const Vec2& delta) const {
            return translated(delta.x, delta.y);
        }

        /* =========================
           Equality
           ========================= */

        constexpr bool operator==(const Rect& other) const {
            return x == other.x && y == other.y &&
                w == other.w && h == other.h;
        }

        constexpr bool operator!=(const Rect& other) const {
            return !(*this == other);
        }
    };

} // namespace blaze