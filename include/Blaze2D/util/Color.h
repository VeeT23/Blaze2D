#pragma once
#include <cstdint>

struct SDL_Renderer; // Forward declare

namespace blaze
{
    struct Color
    {
        float r, g, b, a;

        Color(); // Defaults to black
        Color(uint8_t r8, uint8_t g8, uint8_t b8, uint8_t a8 = 255);
        Color(int r8, int g8, int b8, int a8 = 255);
        Color(float rf, float gf, float bf, float af = 1.f);
    };

    inline void set_render_draw_color(SDL_Renderer* renderer, const Color& c);

    static Color lerp(const Color& a, const Color& b, float t);
}
