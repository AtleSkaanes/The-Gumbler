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

	private:
		void initWindow();

		const int width;
		const int height;

		std::string windowName;
		GLFWwindow* window;
	};
} // namespace atle