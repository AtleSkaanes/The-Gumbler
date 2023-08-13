
#include "first_app.hpp"

namespace atle
{
	void FirstApp::Run()
	{
		while(!atleWindow.ShouldClose())
		{
			glfwPollEvents();
		}
	}

} // namespace atle