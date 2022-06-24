#include "window.h"
#include <stdexcept>

namespace Dyna
{
	EngineWindow::EngineWindow(int widht, int height, std::string name)
		: WIDTH{ widht }, HEIGHT{ height }, windowName{ name }
	{
		initWindow();
	}
	EngineWindow::~EngineWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	bool EngineWindow::shouldClose()
	{
		return glfwWindowShouldClose(window);
	}
	void EngineWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("failed To create window Surface");
		}
	}
	void EngineWindow::frameBufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto currentwindow = reinterpret_cast<EngineWindow*>(glfwGetWindowUserPointer(window));
		currentwindow->frameBufferResized = true;
		currentwindow->WIDTH = width;
		currentwindow->HEIGHT = height;

	}
	void EngineWindow::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(WIDTH, HEIGHT, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
	}
}