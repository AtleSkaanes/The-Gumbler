#pragma once

#include "atle_window.hpp"

namespace atle
{
	class FirstApp
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void Run();

	private:
		AtleWindow atleWindow{ WIDTH, HEIGHT, "AAAAAAAA" };

	};

} // namespace atle