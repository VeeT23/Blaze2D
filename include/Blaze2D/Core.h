#pragma once

#include <cstdint>

namespace blaze {

	/**
	 * Initializes Blaze2D.
	 *
	 * Safe to call multiple times.
	 * SDL is initialized lazily when subsystems (Window, Renderer, etc.) are used.
	 */
	bool Init();

	/**
	 * Shuts down Blaze2D.
	 *
	 * Destroys internal systems and shuts down SDL if Blaze owns its lifetime.
	 * Safe to call multiple times.
	 */
	void Shutdown();

	/**
	 * Returns true if Blaze2D has been initialized.
	 */
	bool IsInitialized();

} // namespace blaze
