#pragma once

#include "atle_window.hpp"
#include "atle_pipeline.hpp"

namespace atle
{
	class FirstApp
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void Run();

	private:
		AtleWindow atleWindow{ WIDTH, HEIGHT, "AAAAAAAA" };
		AtlePipeline atlePipeline{ "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv" };
	};

} // namespace atle