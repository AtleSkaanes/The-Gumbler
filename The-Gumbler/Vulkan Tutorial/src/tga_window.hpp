#pragma once

#define GLEW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace tga
{
	class TgaWindow
	{
	public:
		TgaWindow(int w, int h, std::string name);
		~TgaWindow();

		TgaWindow(const TgaWindow&) = delete;
		TgaWindow& operator=(const TgaWindow&) = delete;

		bool ShouldClose() { return glfwWindowShouldClose(window); }

	private:
		void initWindow();

		const int width;
		const int height;

		std::string windowName;
		GLFWwindow* window;
	};
}  // namespace tga