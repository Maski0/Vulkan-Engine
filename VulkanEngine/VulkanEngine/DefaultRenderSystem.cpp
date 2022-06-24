#include "DefaultRenderSystem.h"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

namespace Dyna
{
	struct SimplePushConstantData {
		glm::mat4 transform{ 1.f };
		alignas(16) glm::vec3 color;
	};

	DefaultRenderSystem::DefaultRenderSystem(EngineDevice& device, VkRenderPass renderPass)
		:eDevice{device}
	{
		createPipelineLayout();
		createPipeline(renderPass);
	}

	DefaultRenderSystem::~DefaultRenderSystem()
	{
		vkDestroyPipelineLayout(eDevice.device(), pipelineLayout, nullptr);
	}

	void DefaultRenderSystem::renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameEntity>& gameObjects)
	{
		ePipeline->bind(commandBuffer);

		for (auto& obj : gameObjects) {
			obj.transform.rotation.y = glm::mod(obj.transform.rotation.y + 0.001f, glm::two_pi<float>());
			obj.transform.rotation.x = glm::mod(obj.transform.rotation.x + 0.0005f, glm::two_pi<float>());

			SimplePushConstantData push{};
			push.color = obj.color;
			push.transform = obj.transform.mat4();

			vkCmdPushConstants(
				commandBuffer,
				pipelineLayout,
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
				0,
				sizeof(SimplePushConstantData),
				&push);
			obj.model->bind(commandBuffer);
			obj.model->draw(commandBuffer);
		}
	}

	void DefaultRenderSystem::createPipelineLayout()
	{
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(SimplePushConstantData);

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
		if (vkCreatePipelineLayout(eDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
			VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}

	void DefaultRenderSystem::createPipeline(VkRenderPass renderPass)
	{
		assert(pipelineLayout != NULL && "Cannot create pipeline before pipeline layout");

		PipelineConfigInfo pipelineConfig{};
		Pipeline::defaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = renderPass;
		pipelineConfig.pipelineLayout = pipelineLayout;
		ePipeline = std::make_unique<Pipeline>(
			eDevice,
			"shaders/Base_Shader.vert.spv",
			"shaders/Base_Shader.frag.spv",
			pipelineConfig);
	}

}