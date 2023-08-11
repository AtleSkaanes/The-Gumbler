#pragma once
#include <string>
#include <vector>

namespace tga
{
	class TgaPipeline
	{
	public:
		TgaPipeline(const std::string& vertFilepath, const std::string& fragFilepath);

	private:
		static std::vector<char> ReadFile(const std::string& filepath);

		void CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
	};

}  // namespace tga