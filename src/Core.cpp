
#include <Blaze2D/Core.h>
#include <atomic>

#include "Blaze2D/internal/SDLManager.h"


namespace blaze {

    namespace {
        std::atomic<bool> g_initialized{ false };
    }

    bool Init()
    {
        bool expected = false;
        if (!g_initialized.compare_exchange_strong(expected, true)) {
            // Already initialized
            return true;
        }

        // Nothing to initialize yet.
        // SDL is initialized lazily by subsystems.
        return true;
    }

    void Shutdown()
    {
        bool expected = true;
        if (!g_initialized.compare_exchange_strong(expected, false)) {
            // Not initialized or already shut down
            return;
        }

        blaze::detail::shutdown_sdl();
    }

    bool IsInitialized()
    {
        return g_initialized.load();
    }

} // namespace blaze
