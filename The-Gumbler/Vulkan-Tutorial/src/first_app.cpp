#include "first_app.hpp"

#include <stdexcept>
#include <array>

namespace tga
{

	FirstApp::FirstApp()
	{
		LoadModels();
		CreatePipelineLayout();
		RecreateSwapChain();
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
			DrawFrame();
		}

		vkDeviceWaitIdle(tgaDevice.device());
	}


	void FirstApp::LoadModels()
	{
		std::vector<TgaModel::Vertex> verticies{
			{{0.0f, -0.75f}, {1.0f, 0.0f, 0.0f}},
			{{0.75f, 0.75f}, {0.0f, 1.0f, 0.0f}},
			{{-0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}}
		};


		tgaModel = std::make_unique<TgaModel>(tgaDevice, verticies);
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
		PipelineConfigInfo pipelineConfig{};
		TgaPipeline::DefaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = tgaSwapChain->getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		tgaPipeline = std::make_unique<TgaPipeline>(
			tgaDevice,
			"shaders/simple_shader.vert.spv",
			"shaders/simple_shader.frag.spv",
			pipelineConfig);
	}

	void FirstApp::RecreateSwapChain()
	{
		auto extent = tgaWindow.GetExtent();
		while (extent.width == 0 || extent.height == 0)
		{
			extent = tgaWindow.GetExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(tgaDevice.device());

		if (tgaSwapChain == nullptr)
			tgaSwapChain = std::make_unique<TgaSwapChain>(tgaDevice, extent);
		else
		{
			tgaSwapChain = std::make_unique<TgaSwapChain>(tgaDevice, extent, std::move(tgaSwapChain));
			if (tgaSwapChain->imageCount() != commandBuffers.size())
			{
				FreeCommandBuffers();
				CreateCommandBuffers();
			}
		}

		CreatePipeline();
	}

	void FirstApp::CreateCommandBuffers()
	{
		commandBuffers.resize(tgaSwapChain->imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = tgaDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(tgaDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers!");
	}

	void FirstApp::FreeCommandBuffers()
	{
		vkFreeCommandBuffers(tgaDevice.device(), tgaDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void FirstApp::RecordCommandBuffer(int imageIndex)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("failed to begin recording command buffer!");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = tgaSwapChain->getRenderPass();
		renderPassInfo.framebuffer = tgaSwapChain->getFrameBuffer(imageIndex);

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = tgaSwapChain->getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(tgaSwapChain->getSwapChainExtent().width);
		viewport.height = static_cast<float>(tgaSwapChain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, tgaSwapChain->getSwapChainExtent() };
		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

		tgaPipeline->bind(commandBuffers[imageIndex]);
		tgaModel->Bind(commandBuffers[imageIndex]);
		tgaModel->Draw(commandBuffers[imageIndex]);

		vkCmdEndRenderPass(commandBuffers[imageIndex]);
		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
			throw std::runtime_error("failed to record command buffer");
	}

	void FirstApp::DrawFrame()
	{
		uint32_t imageIndex;
		auto result = tgaSwapChain->acquireNextImage(&imageIndex);
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("failed to acquire swap chain image!");

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			RecreateSwapChain();
			return;
		}

		RecordCommandBuffer(imageIndex);
		result = tgaSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || tgaWindow.WasWindowResized())
		{
			tgaWindow.ResetWindowResizedFlag();
			RecreateSwapChain();
			return;
		}

		if (result != VK_SUCCESS)
			throw std::runtime_error("failed to present swap chain image!");
	}

#pragma region funStuff
	std::vector<TgaModel::Vertex> FirstApp::SierpinskiTriangle(const std::array<TgaModel::Vertex, 3>& input, uint8_t depth)
	{

		// Generate the upsidedown inverted triangle
		std::array<TgaModel::Vertex, 3> upsideTriangle{{
			{{(input[0].position.x + input[2].position.x) / 2, (input[0].position.y + input[2].position.y) / 2}},
			{{(input[0].position.x + input[1].position.x) / 2, (input[0].position.y + input[1].position.y) / 2}},
			{{(input[1].position.x + input[2].position.x) / 2, (input[1].position.y + input[2].position.y) / 2}}
			}};

		std::array<std::array<TgaModel::Vertex, 3>, 3> subTriangles{{
			// Triangle 1
			{{
			{{input[0].position}},
			{{upsideTriangle[1].position}},
			{{upsideTriangle[0].position}}
			}},
			// Triangle 2
			{{
			{{upsideTriangle[1].position}},
			{{input[1].position}},
			{{upsideTriangle[2].position}}
			}},
			// Triangle 3
			{{
			{{upsideTriangle[0].position}},
			{{upsideTriangle[2].position}},
			{{input[2].position}}
			}}
			}};

		if (depth <= 1)
			return std::vector<TgaModel::Vertex>{input[0], input[1], input[2]};

		std::vector<TgaModel::Vertex> verticies{};
		for (const std::array<TgaModel::Vertex, 3>& triangle: subTriangles)
		{
			auto newSubTriangles = SierpinskiTriangle(triangle, depth - 1);
			verticies.insert(std::end(verticies), std::begin(newSubTriangles), std::end(newSubTriangles));
		}

		return verticies;
	}

#pragma endregion


} // namespace tga