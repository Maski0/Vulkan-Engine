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
		/*std::string filepath = FileDialogs::OpenFile(appwindow.getGlfWwindow(), "OBJ Files (*.obj)\0 *.obj\0 ");
		if (!filepath.empty())
		{
			ModelFilePath = filepath;
			std::cout << filepath << "\n";
		}*/
		ModelFilePath = "models/smooth_vase.obj";
		loadGameEntitys();
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
	

	
	void BasicApp::loadGameEntitys()
	{
		std::shared_ptr<EngineModel> lveModel = EngineModel::createModelFromFile(appDevice, ModelFilePath);
		auto gameObj = GameEntity::createGameEntity();
		gameObj.model = lveModel;
		gameObj.transform.translation = { .0f, .0f, 2.5f };
		gameObj.transform.scale = glm::vec3(3.f);
		gameObjects.push_back(std::move(gameObj));
	}
	
}