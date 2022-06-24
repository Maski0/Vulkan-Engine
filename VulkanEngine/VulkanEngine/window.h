#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace Dyna
{
	class EngineWindow 
	{
	public:
		EngineWindow(int widht, int height, std::string name);
		~EngineWindow();

		EngineWindow(const EngineWindow&) = delete;
		EngineWindow&operator=(const EngineWindow &) = delete;

		bool shouldClose();

		VkExtent2D getExtent() { return { static_cast<uint32_t>(WIDTH),static_cast<uint32_t>(HEIGHT) }; }

		bool wasWindowResized() { return frameBufferResized; }
		void resetWindowResizedFlag() { frameBufferResized = false; }

		void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
	private:
		static void frameBufferResizeCallback(GLFWwindow* window, int width, int height);
		void initWindow();
		
		int WIDTH;
		int HEIGHT;

		bool frameBufferResized = false;

		std::string windowName;
		GLFWwindow* window;
	};

}