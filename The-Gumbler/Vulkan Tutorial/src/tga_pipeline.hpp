#pragma once
#include "tga_device.hpp"

#include <string>
#include <vector>

namespace tga
{

	struct PipelineConfigInfo{};

	class TgaPipeline
	{
	public:
		TgaPipeline(
			TgaDevice& device,
			const std::string& vertFilepath,
			const std::string& fragFilepath,
			const PipelineConfigInfo& configInfo);

		~TgaPipeline() {};

		TgaPipeline(const TgaPipeline&) = delete;
		void operator=(const TgaPipeline&) = delete;

		static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);

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