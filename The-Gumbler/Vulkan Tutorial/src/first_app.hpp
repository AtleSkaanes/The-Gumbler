#pragma once

#include "tga_window.hpp"
#include "tga_pipeline.hpp"

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
		TgaPipeline tgaPipeline{ "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv" };
	};
}