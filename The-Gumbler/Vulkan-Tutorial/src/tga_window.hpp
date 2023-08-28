#pragma once

#define GLFW_INCLUDE_VULKAN
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
		VkExtent2D GetExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }
		bool WasWindowResized() { return framebufferResized; }
		void ResetWindowResizedFlag() { framebufferResized = false; }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	private:
		static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);
		void initWindow();

		int width;
		int height;
		bool framebufferResized = false;

		std::string windowName;
		GLFWwindow* window;
	};
}  // namespace tga