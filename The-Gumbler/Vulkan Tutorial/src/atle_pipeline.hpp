#pragma once

#include "atle_device.hpp"

// std
#include <string>
#include <vector>

namespace atle
{
	struct PipelineConfigInfo
	{
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class AtlePipeline
	{
	public:
		AtlePipeline(AtleDevice &device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo configInfo);

		~AtlePipeline();

		AtlePipeline(const AtlePipeline&) = delete;
		void operator=(const AtlePipeline&) = delete;


		static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);
	private:
		static std::vector<char> ReadFile(const std::string& filepath);

		void CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo configInfo);

		void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		AtleDevice& atleDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};

} // namespace atle