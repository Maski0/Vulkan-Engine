#pragma once

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"


namespace Dyna
{
	class Camera
	{
	public:

		void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);

		void setPrespectiveProjection(float fovy, float aspect, float near, float far);

		void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{ 0.f, -1.f, 0.f });

		void setViewTarget(glm::vec3 position, glm::vec3 Target, glm::vec3 up = glm::vec3{ 0.f, -1.f, 0.f });

		void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

		const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
		const glm::mat4& getViewMatrix() const { return viewMatrix; }
	private:

		glm::mat4 projectionMatrix{ 1.f };
		glm::mat4 viewMatrix{ 1.f };
	};
}