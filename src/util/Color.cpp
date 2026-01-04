#include "Blaze2D/util/Color.h"
#include "Blaze2D/internal/SDLManager.h"

namespace blaze
{
	Color::Color() : r(0.f), g(0.f), b(0.f), a(0.f) {};

	Color::Color(uint8_t r8, uint8_t g8, uint8_t b8, uint8_t a8) :
        r(r8 / 255.f),
        g(g8 / 255.f),
        b(b8 / 255.f),
        a(a8 / 255.f)
    {
    }

    Color::Color(int r8, int g8, int b8, int a8) :
        r(r8 / 255.f),
        g(g8 / 255.f),
        b(b8 / 255.f),
        a(a8 / 255.f)
    {
    }

    Color::Color(float rf, float gf, float bf, float af) :
        r(rf),
        g(gf),
        b(bf),
        a(af)
    {
    }

    inline void set_render_draw_color(SDL_Renderer* renderer, const Color& c)
    {
        SDL_SetRenderDrawColor(
            renderer,
            (uint8_t)(c.r * 255),
            (uint8_t)(c.g * 255),
            (uint8_t)(c.b * 255),
            (uint8_t)(c.a * 255)
        );
    }

    static Color lerp(const Color& a, const Color& b, float t)
    {
        return {
            a.r + (b.r - a.r) * t,
            a.g + (b.g - a.g) * t,
            a.b + (b.b - a.b) * t,
            a.a + (b.a - a.a) * t
        };
    }
} // namespace blaze