#pragma once

#include <cstdint>

namespace blaze::detail {

	void ensure_sdl(uint32_t flags);
	void shutdown_sdl();

	bool is_initialized(uint32_t flags);

}