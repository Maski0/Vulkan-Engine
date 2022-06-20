#include "window.h"
#include <stdexcept>

namespace Dyna
{
	Window::Window(int widht, int height, std::string name)
		: WIDTH{ widht }, HEIGHT{ height }, windowName{ name }
	{
		initWindow();
	}
	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(window);
	}
	void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("failed To create window Surface");
		}
	}
	void Window::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, windowName.c_str(), nullptr, nullptr);

	}
}