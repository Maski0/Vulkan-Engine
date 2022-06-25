#pragma once

#include "GLFW/glfw3.h"

//std
#include <string>

namespace Dyna
{
	class FileDialogs
	{

	public:
		static std::string OpenFile(GLFWwindow* window, const char* filter);
		static std::string SaveFile(GLFWwindow* window, const char* filter);
	};
}