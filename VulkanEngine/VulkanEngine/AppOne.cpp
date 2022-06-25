#include "AppOne.h"
#include "DefaultRenderSystem.h"
#include "EngineCamera.h"
#include "WindowsPlatformUtils/PlatformUtils.h"
#include "Keyboard_Movement_controller.h"

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"


#include<stdexcept>
#include <chrono>
#include <cassert>
#include<array>
#include <string>
#include <iostream>

namespace Dyna
{

	BasicApp::BasicApp()
	{
		loadGameEntitys();
		/*std::string filepath = FileDialogs::OpenFile(appwindow.getGlfWwindow(), "OBJ Files (*.obj)\0 *.obj\0 ");
		if (!filepath.empty())
		{
			std::cout << filepath << "\n";
		}*/
	}
	BasicApp::~BasicApp()
	{
	}
	

	void BasicApp::run()
	{
		DefaultRenderSystem defaultRenderSystem{ appDevice, appRenderer.getSwapChainRenderPass() };
		Camera camera{};
		//camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.0f));
		//camera.setViewTarget(glm::vec3(-1.f, -2.f, 6.f), glm::vec3(0.f, 0.f, 2.5f));

		auto viewerObject = GameEntity::createGameEntity();
		KeyboardMovementController cameraController{};

		auto currentTime = std::chrono::high_resolution_clock::now();


		while (!appwindow.shouldClose())
		{
			glfwPollEvents();

			auto newTime = std::chrono::high_resolution_clock::now();
			float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
			currentTime = newTime;

			//frameTime = glm::min(frameTime, 60.0f);

			cameraController.moveInPlaneXZ(appwindow.getGlfWwindow(), frameTime, viewerObject);
			camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

			float aspect = appRenderer.getAspectRatio();
			//camera.setOrthographicProjection(-aspect, aspect, -1, 1, -1, 1);
			camera.setPrespectiveProjection(glm::radians(50.f), aspect, 0.1f, 50.f);

			if (auto commandBuffer = appRenderer.beginFrame()) 
			{
				appRenderer.beginSwapChainRenderPass(commandBuffer);
				defaultRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
				appRenderer.endSwapChainRenderPass(commandBuffer);
				appRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(appDevice.device());
	}

	// temporary helper function, creates a 1x1x1 cube centered at offset
	std::unique_ptr<EngineModel> createCubeModel(EngineDevice& device, glm::vec3 offset) 
	{
		EngineModel::Builder modelBuilder{};
		modelBuilder.vertices = {

			// left face (white)
			{{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
			{{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
			{{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
			{{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},

			// right face (yellow)
			{{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
			{{.5f, .5f, .5f}, {.8f, .8f, .1f}},
			{{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
			{{.5f, .5f, -.5f}, {.8f, .8f, .1f}},

			// top face (orange, y axis points down)
			{{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
			{{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
			{{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
			{{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},

			// bottom face (red)
			{{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
			{{.5f, .5f, .5f}, {.8f, .1f, .1f}},
			{{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
			{{.5f, .5f, -.5f}, {.8f, .1f, .1f}},

			// nose face (blue)
			{{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
			{{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
			{{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
			{{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},

			// tail face (green)
			{{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
			{{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
			{{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
			{{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},

		};
		for (auto& v : modelBuilder.vertices) {
			v.position += offset;
		}
		modelBuilder.indices = { 0,  1,  2,  0,  3,  1,  4,  5,  6,  4,  7,  5,  8,  9,  10, 8,  11, 9,
						  12, 13, 14, 12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22, 20, 23, 21 };
		return std::make_unique<EngineModel>(device, modelBuilder);
	}


	
	void BasicApp::loadGameEntitys()
	{
		std::shared_ptr<EngineModel> lveModel = createCubeModel(appDevice, { .0f, .0f, .0f });
		auto cube = GameEntity::createGameEntity();
		cube.model = lveModel;
		cube.transform.translation = { .0f, .0f, 2.5f };
		cube.transform.scale = { .5f, .5f, .5f };
		gameObjects.push_back(std::move(cube));
	}
	
}