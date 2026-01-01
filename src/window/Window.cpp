#include "Blaze2D/window/Window.h"
#include "Blaze2D/internal/SDLManager.h"

#include <iostream>

namespace blaze {

    Window::Window(const std::string _name, const int _width, const int _height, const std::string _title)
        : name(_name), width(_width), height(_height) {

        //Assigns title if set
        title = (_title == "") ? _name : _title;

        detail::ensure_sdl(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

        

        window = SDL_CreateWindow(
            title.c_str(),
            width,
            height,
            SDL_WINDOW_RESIZABLE
        );

        if (!window) {
            throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
        }

        renderer = SDL_CreateRenderer(window, nullptr);

        if (!renderer) {
            SDL_DestroyWindow(window);
            window = nullptr;
            throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
        }

       

    }

    Window::~Window() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        
    }

} // namespace blaze
