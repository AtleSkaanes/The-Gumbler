#pragma once

#include "tga_window.hpp"
#include "tga_pipeline.hpp"
#include "tga_device.hpp"

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
		TgaDevice tgaDevice{ tgaWindow };
		TgaPipeline tgaPipeline{
			tgaDevice,
			"shaders/simple_shader.vert.spv",
			"shaders/simple_shader.frag.spv",
			TgaPipeline::DefaultPipelineConfigInfo(WITDH, HEIGHT)};
	};
}