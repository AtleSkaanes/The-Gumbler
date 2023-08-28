#pragma once

#include "tga_window.hpp"
#include "tga_pipeline.hpp"
#include "tga_device.hpp"
#include "tga_swap_chain.hpp"
#include "tga_model.hpp"

// std
#include "memory"
#include "vector"

namespace tga
{
	class FirstApp
	{
	public:
		static constexpr int WITDH = 1440;
		static constexpr int HEIGHT = 920;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void Run();

	private:
		void LoadModels();
		void CreatePipelineLayout();
		void CreatePipeline();
		void CreateCommandBuffers();
		void FreeCommandBuffers();
		void DrawFrame();
		void RecreateSwapChain();
		void RecordCommandBuffer(int imageIndex);

		std::vector<TgaModel::Vertex> SierpinskiTriangle(const std::array<TgaModel::Vertex, 3>& input, uint8_t depth);

		TgaWindow tgaWindow{ WITDH, HEIGHT, "boo!" };
		TgaDevice tgaDevice{ tgaWindow };
		std::unique_ptr<TgaSwapChain> tgaSwapChain;
		std::unique_ptr<TgaPipeline> tgaPipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::unique_ptr<TgaModel> tgaModel;
	};
}