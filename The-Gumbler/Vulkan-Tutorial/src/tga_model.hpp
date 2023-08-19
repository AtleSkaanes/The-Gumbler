#pragma once

#include "tga_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace tga
{
	class TgaModel
	{
	public:

		struct Vertex
		{
			glm::vec2 position;

			static std::vector<VkVertexInputBindingDescription> GetBindingDesciptions();
			static std::vector<VkVertexInputAttributeDescription> GetAttributeDesciptions();
		};

		TgaModel(TgaDevice& device, const std::vector<Vertex>& verticies);
		~TgaModel();

		TgaModel(const TgaModel&) = delete;
		TgaModel& operator=(const TgaModel&) = delete;

		void Bind(VkCommandBuffer commandBuffer);
		void Draw(VkCommandBuffer commandBuffer);

	private:
		void CreateVertexBuffers(const std::vector<Vertex>& verticies);

		TgaDevice& tgaDevice;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;
	};
}