#include "atle_window.hpp"

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



} // namespace atle