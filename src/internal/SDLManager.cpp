
#include <SDL3/SDL.h>
#include <mutex>

#include "blaze/internal/SDLManager.h"


namespace blaze::detail {

    namespace {
        std::mutex sdl_mutex;

        // Bitmask of initialized SDL subsystems
        uint32_t initialized_flags = 0;

        // Whether Blaze2D is responsible for calling SDL_Quit
        bool manage_lifetime = true;

        bool init_subsystems(uint32_t flags)
        {
            if (flags == 0)
                return true;

            if (SDL_InitSubSystem(flags) != 0)
                return false;

            initialized_flags |= flags;
            return true;
        }
    }

    void ensure_sdl(uint32_t flags)
    {
        std::lock_guard<std::mutex> lock(sdl_mutex);

        // First-time init (base SDL)
        if (initialized_flags == 0) {
            if (SDL_Init(0) != 0) {
                SDL_Log("Blaze2D: SDL_Init failed: %s", SDL_GetError());
                return;
            }
        }

        // Initialize missing subsystems
        uint32_t missing = flags & ~initialized_flags;
        if (missing) {
            if (!init_subsystems(missing)) {
                SDL_Log("Blaze2D: SDL_InitSubSystem failed: %s", SDL_GetError());
            }
        }
    }

    bool is_initialized(uint32_t flags)
    {
        std::lock_guard<std::mutex> lock(sdl_mutex);
        return (initialized_flags & flags) == flags;
    }

    void shutdown_sdl()
    {
        std::lock_guard<std::mutex> lock(sdl_mutex);

        if (!manage_lifetime || initialized_flags == 0)
            return;

        SDL_Quit();
        initialized_flags = 0;
    }

} // namespace blaze::detail
