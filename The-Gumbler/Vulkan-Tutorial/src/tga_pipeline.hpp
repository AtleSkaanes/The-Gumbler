#pragma once
#include "tga_device.hpp"

#include <string>
#include <vector>

namespace tga
{

	struct PipelineConfigInfo
	{
		PipelineConfigInfo() = default;

		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		std::vector<VkDynamicState> dynamicStateEnables;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class TgaPipeline
	{
	public:
		TgaPipeline(
			TgaDevice& device,
			const std::string& vertFilepath,
			const std::string& fragFilepath,
			const PipelineConfigInfo& configInfo);

		~TgaPipeline();

		TgaPipeline() = default;

		TgaPipeline(const TgaPipeline&) = delete;
		TgaPipeline& operator=(const TgaPipeline&) = delete;

		void bind(VkCommandBuffer commandBuffer);

		static void DefaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

	private:
		static std::vector<char> ReadFile(const std::string& filepath);

		void CreateGraphicsPipeline(
			const std::string& vertFilepath,
			const std::string& fragFilepath,
			const PipelineConfigInfo& configInfo);

		void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		TgaDevice& tgaDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};

}  // namespace tga