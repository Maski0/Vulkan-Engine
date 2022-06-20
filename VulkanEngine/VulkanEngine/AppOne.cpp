#include "AppOne.h"

namespace Dyna
{
	void firstApp::run()
	{
		while (!appwindow.shouldClose())
		{
			glfwPollEvents();

		}
	}
}