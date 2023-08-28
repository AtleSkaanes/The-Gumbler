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
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, FrameBufferResizedCallback);
	}

	void AtleWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create window surface");
		}
	}


	void AtleWindow::FrameBufferResizedCallback(GLFWwindow* window, int width, int height)
	{
		auto atleWindow = reinterpret_cast<AtleWindow*>(glfwGetWindowUserPointer(window));
		atleWindow->frameBufferResized = true;
		atleWindow->width = width;
		atleWindow->height = height;
	}



} // namespace atle