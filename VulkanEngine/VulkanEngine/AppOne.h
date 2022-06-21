#pragma once

#include "window.h"
#include "pipeline.h"
#include "Vulkan_device.h"
#include "SwapChain.h"
#include "EngineModel.h"
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
		void loadModels();
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		Window appwindow{ Width,Height,"Dyna App" };
		EngineDevice appDevice{ appwindow };
		EngineSwapChain appSwapChain{ appDevice,appwindow.getExtent() };
		/*Pipeline appPipeline{ 
			appDevice,
			"shaders/Base_shader.vert.spv",
			"shaders/Base_shader.frag.spv", 
			Pipeline::defaultPipelineConfigInfo(Width,Height) };*/

		std::unique_ptr<Pipeline> appPipeline;
		std::unique_ptr<EngineModel> appModel;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}