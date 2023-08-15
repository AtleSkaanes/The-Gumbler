
#include "first_app.hpp"

// std
#include <stdexcept>

namespace atle
{
	FirstApp::FirstApp()
	{
		CreatePiepelineLayout();
		CreatePipeline();
		CreateCommandBuffers();
	}

	FirstApp::~FirstApp()
	{
		vkDestroyPipelineLayout(atleDevice.device(), pipelineLayout, nullptr);
	}


	void FirstApp::Run()
	{
		while(!atleWindow.ShouldClose())
		{
			glfwPollEvents();
		}
	}

	void FirstApp::CreatePiepelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(atleDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create pipeline layout");
		} 
	}

	void FirstApp::CreatePipeline()
	{
		auto pipelineConfig = AtlePipeline::DefaultPipelineConfigInfo(atleSwapChain.width(), atleSwapChain.height());
		pipelineConfig.renderPass = atleSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;

		atlePipeline = std::make_unique<AtlePipeline>(
			atleDevice,
			"shaders/simple_shader.vert.spv",
			"shaders/simple_shader.frag.spv",
			pipelineConfig
		);
		
	}

	void FirstApp::CreateCommandBuffers()
	{
			
	}

	void FirstApp::DrawFrame()
	{
		
	}


} // namespace atle