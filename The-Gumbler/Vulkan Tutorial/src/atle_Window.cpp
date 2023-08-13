#include "atle_window.hpp"

// std
#include <stdexcept>

namespace atle
{
	AtleWindow::AtleWindow(int w, int h, std::string name)
		: width{w}, height{h}, windowName{name}
	{
		initWindow();
	}

	AtleWindow::~AtleWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void AtleWindow::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}

	void AtleWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create window surface");
		}
	}



} // namespace atle