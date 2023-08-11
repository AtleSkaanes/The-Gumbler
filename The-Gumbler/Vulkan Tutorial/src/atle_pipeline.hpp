#pragma once

#include <string>
#include <vector>

namespace atle
{
	class AtlePipeline
	{
	public:
		AtlePipeline(const std::string& vertFilepath, const std::string& fragFilepath);

	private:
		static std::vector<char> ReadFile(const std::string& filepath);

		void CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
	};

} // namespace atle