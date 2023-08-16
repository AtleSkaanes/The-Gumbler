#include "tga_window.hpp"


#include <stdexcept>

namespace tga
{
	TgaWindow::TgaWindow(int w, int h, std::string name)
		: width{w}, height{h}, windowName{name}
	{
		initWindow();
	}

	TgaWindow::~TgaWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void TgaWindow::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}

	void TgaWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create window surface");
		}
	}

} // namespace tga