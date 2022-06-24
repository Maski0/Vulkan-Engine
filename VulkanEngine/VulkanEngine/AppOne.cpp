#include "AppOne.h"
#include "DefaultRenderSystem.h"

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"


#include<stdexcept>
#include <cassert>
#include<array>

namespace Dyna
{

	BasicApp::BasicApp()
	{
		loadGameEntitys();
	}
	BasicApp::~BasicApp()
	{
	}
	void BasicApp::run()
	{
		DefaultRenderSystem defaultRenderSystem{ appDevice, appRenderer.getSwapChainRenderPass() };

		while (!appwindow.shouldClose())
		{
			glfwPollEvents();

			if (auto commandBuffer = appRenderer.beginFrame()) 
			{
				appRenderer.beginSwapChainRenderPass(commandBuffer);
				defaultRenderSystem.renderGameObjects(commandBuffer, gameObjects);
				appRenderer.endSwapChainRenderPass(commandBuffer);
				appRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(appDevice.device());
	}
	void BasicApp::sierpinski(std::vector<EngineModel::Vertex>& vertices, int depth, glm::vec2 left, glm::vec2 right, glm::vec2 top)
	{
		if (depth <= 0) {
			vertices.push_back({ top });
			vertices.push_back({ right });
			vertices.push_back({ left });
		}
		else {
			auto leftTop = 0.5f * (left + top);
			auto rightTop = 0.5f * (right + top);
			auto leftRight = 0.5f * (left + right);
			sierpinski(vertices, depth - 1, left, leftRight, leftTop);
			sierpinski(vertices, depth - 1, leftRight, right, rightTop);
			sierpinski(vertices, depth - 1, leftTop, rightTop, top);
		}
	}
	void BasicApp::loadGameEntitys()
	{
		std::vector<EngineModel::Vertex> vertices{
			{{0.0f,-0.5f}, {1.0f,0.0f,0.0f}},
			{{0.5f, 0.5f}, {0.0f,1.0f,0.0f}},
			{{-0.5f,0.5f}, {0.0f,0.0f,1.0f}}
		};
		/*std::vector<EngineModel::Vertex> vertices{};
		sierpinski(vertices, 0, { -0.5f, 0.5f }, { 0.5f, 0.5f }, { 0.0f, -0.5f });*/
		auto appModel = std::make_shared<EngineModel>(appDevice, vertices);

		auto triangle = GameEntity::createGameEntity();
		triangle.model = appModel;
		triangle.color = { 0.1f,0.8f,0.1f };
		triangle.transform2d.translation.x = .2f;
		triangle.transform2d.scale = { 2.0f,0.5f };
		triangle.transform2d.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}
	
}