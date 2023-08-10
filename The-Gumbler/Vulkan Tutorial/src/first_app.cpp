#include "first_app.hpp"

namespace tga
{
	void FirstApp::Run()
	{
		while (!tgaWindow.ShouldClose())
		{
			glfwPollEvents();
		}
	}
} // namespace tga