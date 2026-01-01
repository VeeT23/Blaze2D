
#include <Blaze2D/App.h>
#include <stdexcept>

#include "Blaze2D/internal/SDLManager.h"


namespace blaze {

    App::App() {
        // Nothing to initialize yet.
        // SDL is initialized lazily by subsystems.
    }

    App::~App() {
        blaze::detail::shutdown_sdl();
    }

    Window& App::createWindow(const std::string name, const int width, const int height, const std::string title)
    {
        windows.push_back(std::make_unique<Window>(name, width, height, title));
        return *windows.back();
    }

    Window& App::getWindow(const std::string& name)
    {
        for (auto& win : windows) {
            if (win->getName() == name)
                return *win;
        }
        throw std::runtime_error("Window not found: " + name);
    }

    void Shutdown()
    {
        blaze::detail::shutdown_sdl();
    }
} // namespace blaze
