#pragma once

#include "Vulkan_device.h"


#include <string>
#include <vector>

namespace Dyna
{
	struct PipelineConfigInfo
	{
		PipelineConfigInfo() = default;
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		std::vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		VkPipelineLayout pipelineLayout = NULL;
		VkRenderPass renderPass = NULL;
		uint32_t subpass = 0;

	};

	class Pipeline
	{
	public:
		Pipeline(
			EngineDevice &device, 
			const std::string &vertFilepath, 
			const std::string &fragFilepath, 
			const PipelineConfigInfo &configInfo);
		~Pipeline();
		Pipeline() = default;
		Pipeline(const Pipeline&) = delete;
		Pipeline& operator=(const Pipeline&) = delete;

		void bind(VkCommandBuffer commandBuffer);

		static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

	private:
		static std::vector<char> readFile(const std::string& filePath);

		void createGraphcicsPipeline(
			const std::string& vertFilepath,
			const std::string& fragFilepath, 
			const PipelineConfigInfo& configInfo);

		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		EngineDevice &currentDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};

}