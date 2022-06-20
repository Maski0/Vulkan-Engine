#pragma once

#include "window.h"
#include "pipeline.h"
#include "Vulkan_device.h"

namespace Dyna
{
	class firstApp
	{
	public:
		static constexpr int Width = 800;
		static constexpr int Height = 600;

		void run();
	private:
		Window appwindow{ Width,Height,"Dyna App" };
		EngineDevice appDevice{ appwindow };
		Pipeline appPipeline{ 
			appDevice,
			"shaders/Base_shader.vert.spv",
			"shaders/Base_shader.frag.spv", 
			Pipeline::defaultPipelineConfigInfo(Width,Height) };
	};
}