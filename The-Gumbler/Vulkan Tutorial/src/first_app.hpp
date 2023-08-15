#pragma once

#include "tga_window.hpp"
#include "tga_pipeline.hpp"
#include "tga_device.hpp"
#include "tga_swap_chain.hpp"

// std
#include "memory"
#include "vector"

namespace tga
{
	class FirstApp
	{
	public:
		static constexpr int WITDH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void Run();

	private:
		void CreatePipelineLayout();
		void CreatePipeline();
		void CreateCommandBuffers();
		void DrawFrame();

		TgaWindow tgaWindow{ WITDH, HEIGHT, "boo!" };
		TgaDevice tgaDevice{ tgaWindow };
		TgaSwapChain tgaSwapChain{ tgaDevice, tgaWindow.GetExtent() };
		std::unique_ptr<TgaPipeline> tgaPipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}