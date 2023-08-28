#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace atle
{
	class AtleWindow
	{
	public:
		AtleWindow(int w, int h, std::string name);
		~AtleWindow();

		AtleWindow(const AtleWindow&) = delete;
		AtleWindow& operator=(const AtleWindow&) = delete;

		bool ShouldClose() { return glfwWindowShouldClose(window); }

		VkExtent2D GetExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }
		bool WasWindowResized() { return frameBufferResized; }
		void ResetWindowResizedFlag() { frameBufferResized = false; }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	private:
		static void FrameBufferResizedCallback(GLFWwindow* window, int width, int height);
		void initWindow();

		int width;
		int height;
		bool frameBufferResized = false;

		std::string windowName;
		GLFWwindow* window;
	};
} // namespace atle