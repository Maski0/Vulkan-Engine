#pragma once

#include "Vulkan_device.h"


#include <string>
#include <vector>

namespace Dyna
{
	struct PipelineConfigInfo
	{
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
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

		Pipeline(const Pipeline&) = delete;
		void operator=(const Pipeline&) = delete;

		static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

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