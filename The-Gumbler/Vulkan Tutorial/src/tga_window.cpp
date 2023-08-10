#include "tga_window.hpp"

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

} // namespace tga