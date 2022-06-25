#pragma once
#include "Vulkan_device.h"
#include "GameEntity.h"
#include "pipeline.h"
#include "EngineCamera.h"

// std
#include <memory>
#include <vector>

namespace Dyna
{
	class DefaultRenderSystem
	{
	public:
		DefaultRenderSystem(EngineDevice& device, VkRenderPass renderPass);
		~DefaultRenderSystem();

		DefaultRenderSystem(const DefaultRenderSystem&) = delete;
		DefaultRenderSystem& operator=(const DefaultRenderSystem&) = delete;


		void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameEntity>& gameObjects, const Camera& camera);

	private:
		void createPipelineLayout();
		void createPipeline(VkRenderPass renderPass);

		EngineDevice& eDevice;

		std::unique_ptr<Pipeline> ePipeline;
		VkPipelineLayout pipelineLayout;
	};
}