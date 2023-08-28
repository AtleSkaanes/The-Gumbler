
#include "first_app.hpp"

// std
#include <stdexcept>
#include <array>

namespace atle
{
	FirstApp::FirstApp()
	{
		LoadModels();
		CreatePiepelineLayout();
		RecreateSwapChain();
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
			DrawFrame();
		}

		vkDeviceWaitIdle(atleDevice.device());
	}

	void FirstApp::LoadModels()
	{
		std::vector<AtleModel::Vertex> vertices {
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};
		
		atleModel = std::make_unique<AtleModel>(atleDevice, vertices);
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
		PipelineConfigInfo pipelineConfig{};

		AtlePipeline::DefaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = atleSwapChain->getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;

		atlePipeline = std::make_unique<AtlePipeline>(
			atleDevice,
			"shaders/simple_shader.vert.spv",
			"shaders/simple_shader.frag.spv",
			pipelineConfig
		);
		
	}
	
	void FirstApp::freeCommandBuffers()
	{
		vkFreeCommandBuffers(atleDevice.device(), atleDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
	}


	void FirstApp::RecreateSwapChain()
	{
		auto extent = atleWindow.GetExtent();
		while (extent.width == 0 || extent.height == 0)
		{
			extent = atleWindow.GetExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(atleDevice.device());

		if (atleSwapChain == nullptr)
		{
			atleSwapChain = std::make_unique<AtleSwapChain>(atleDevice, extent);
		} else
		{
			atleSwapChain = std::make_unique<AtleSwapChain>(atleDevice, extent, std::move(atleSwapChain));
			if (atleSwapChain->imageCount() != commandBuffers.size())
			{
				freeCommandBuffers();
				CreateCommandBuffers();
			}
		}

		CreatePipeline();
	}


	void FirstApp::CreateCommandBuffers()
	{
		commandBuffers.resize(atleSwapChain->imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = atleDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(atleDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate command buffers!");
		}

	}

	void FirstApp::RecordCommandBuffer(int imageIndex)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to begin recording command buffer");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = atleSwapChain->getRenderPass();
		renderPassInfo.framebuffer = atleSwapChain->getFrameBuffer(imageIndex);

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = atleSwapChain->getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(atleSwapChain->getSwapChainExtent().width);
		viewport.height = static_cast<float>(atleSwapChain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, atleSwapChain->getSwapChainExtent() };
		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

		atlePipeline->bind(commandBuffers[imageIndex]);
		atleModel->Bind(commandBuffers[imageIndex]);
		atleModel->Draw(commandBuffers[imageIndex]);

		vkCmdEndRenderPass(commandBuffers[imageIndex]);
		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to record command buffer!");
		}
	}

	void FirstApp::DrawFrame()
	{
		uint32_t imageIndex;
		auto result = atleSwapChain->acquireNextImage(&imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			RecreateSwapChain();
			return;
		}
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		RecordCommandBuffer(imageIndex);
		result = atleSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || atleWindow.WasWindowResized())
		{
			atleWindow.ResetWindowResizedFlag();
			RecreateSwapChain();
			return;
		}

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("failed to present swap chain image!");
		}
	}


} // namespace atle