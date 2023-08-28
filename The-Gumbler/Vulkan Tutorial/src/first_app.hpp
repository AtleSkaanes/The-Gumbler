#pragma once

#include "atle_window.hpp"
#include "atle_pipeline.hpp"
#include "atle_device.hpp"
#include "atle_swap_chain.hpp"
#include "atle_model.hpp"

// std
#include <memory>
#include <vector>


namespace atle
{
	class FirstApp
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;


		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void Run();

	private:
		void LoadModels();
		void CreatePiepelineLayout();
		void CreatePipeline();
		void CreateCommandBuffers();
		void DrawFrame();

		AtleWindow atleWindow{ WIDTH, HEIGHT, "AAAAAAAA" };
		AtleDevice atleDevice{ atleWindow };
		AtleSwapChain atleSwapChain{ atleDevice, atleWindow.GetExtent() };
		std::unique_ptr<AtlePipeline> atlePipeline;

		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;

		std::unique_ptr<AtleModel> atleModel;

	};

} // namespace atle