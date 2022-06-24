#pragma once

#include "window.h"
#include "Vulkan_device.h"
#include "EngineRenderer.h"
#include "GameEntity.h"
//std
#include <memory>
#include <vector>

namespace Dyna
{
	class BasicApp
	{
	public:
		static constexpr int Width = 800;
		static constexpr int Height = 600;

		BasicApp();
		~BasicApp();

		BasicApp(const BasicApp&) = delete;
		BasicApp &operator=(const BasicApp &) = delete;

		void run();
	private:
		void sierpinski(
			std::vector<EngineModel::Vertex>& vertices,
			int depth,
			glm::vec2 left,
			glm::vec2 right,
			glm::vec2 top);
		void loadGameEntitys();

		EngineWindow appwindow{ Width,Height,"Dyna App" };
		EngineDevice appDevice{ appwindow };
		EngineRenderer appRenderer{ appwindow,appDevice };

		std::vector<GameEntity> gameObjects;

	};
}