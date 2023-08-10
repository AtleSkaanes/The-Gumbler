#pragma once

#include "tga_window.hpp"

namespace tga
{
class FirstApp
{
public:
	static constexpr int WITDH = 800;
	static constexpr int HEIGHT = 600;

	void Run();

private:
	TgaWindow tgaWindow{ WITDH, HEIGHT, "boo!" };
};


}

