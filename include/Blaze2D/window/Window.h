#pragma once

#include <string>

struct SDL_Window;
struct SDL_Renderer;

namespace blaze {

    class Window {
    public:
        /*
        * Constructs window object
        * Initializes SDL if not already
        */
        Window(const std::string _name, const int _width = 100, const int _height = 100, const std::string _title = "");

        ~Window();

        // Getters
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        std::string getName() const { return name; }
        std::string getTitle() const { return title; }
        SDL_Window* getSDLWindow() const { return window; }
        SDL_Renderer* getRenderer() const { return renderer; }

    private:
        std::string name;
        std::string title;
        int width;
        int height;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    };

} // namespace blaze
