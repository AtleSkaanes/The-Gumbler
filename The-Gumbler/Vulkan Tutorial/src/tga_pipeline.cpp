#include "tga_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace tga
{
	TgaPipeline::TgaPipeline(
		TgaDevice& device,
		const std::string& vertFilepath,
		const std::string& fragFilepath,
		const PipelineConfigInfo& configInfo)
		: tgaDevice{device}
	{
		CreateGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
	}

	std::vector<char> TgaPipeline::ReadFile(const std::string& filepath)
	{
		std::ifstream file{filepath, std::ios::ate | std::ios::binary};
		if (!file.is_open())
		{
			throw std::runtime_error("failed to open file: " + filepath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	void TgaPipeline::CreateGraphicsPipeline(
		const std::string& vertFilepath,
		const std::string& fragFilepath,
		const PipelineConfigInfo& configInfo)
	{
		std::vector<char> vertCode = ReadFile(vertFilepath);
		std::vector<char> fragCode = ReadFile(fragFilepath);

		std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
		std::cout << "Fragment Shader Code Size: " << fragCode.size() << std::endl;

	}

	void TgaPipeline::CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(tgaDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
			throw std::runtime_error("failed to create shader module");
	}

	PipelineConfigInfo TgaPipeline::DefaultPipelineConfigInfo(uint32_t width, uint32_t height)
	{
		PipelineConfigInfo configInfo{};

		return configInfo;
	}

} // namespace tga