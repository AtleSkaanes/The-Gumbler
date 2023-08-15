#include "first_app.hpp"

#include <stdexcept>

namespace tga
{

	FirstApp::FirstApp()
	{
		CreatePipelineLayout();
		CreatePipeline();
		CreateCommandBuffers();
	}
	FirstApp::~FirstApp()
	{
		vkDestroyPipelineLayout(tgaDevice.device(), pipelineLayout, nullptr);
	}

	void FirstApp::Run()
	{
		while (!tgaWindow.ShouldClose())
		{
			glfwPollEvents();
		}
	}

	void FirstApp::CreatePipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(tgaDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create pipeline layout!");
	}

	void FirstApp::CreatePipeline()
	{
		auto pipelineConfig =
			TgaPipeline::DefaultPipelineConfigInfo(tgaSwapChain.width(), tgaSwapChain.height());
		pipelineConfig.renderPass = tgaSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		tgaPipeline = std::make_unique<TgaPipeline>(
			tgaDevice,
			"shaders/simple_shader.vert.spv",
			"shaders/simple_shader.frag.spv",
			pipelineConfig);
	}

	void FirstApp::CreateCommandBuffers(){}
	void FirstApp::DrawFrame(){}

} // namespace tga