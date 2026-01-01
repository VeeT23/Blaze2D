#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <string>
#include "Blaze2D/window/Window.h"

namespace blaze {

	class App {
	public:
		App();
		~App();

		Window& createWindow(const std::string name, const int width = 100, const int height = 100, const std::string title = "");

		Window& getWindow(const std::string& name);

	private:
		std::vector<std::unique_ptr<Window>> windows;
	};

} // namespace blaze
