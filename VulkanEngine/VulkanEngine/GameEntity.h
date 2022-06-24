#pragma once

#include "EngineModel.h"

//std
#include <memory>

namespace Dyna
{
	struct Transform2dComponent
	{
		glm::vec2 translation{};  // (position offset)
		glm::vec2 scale{ 1.f, 1.f };
		float rotation;

		glm::mat2 mat2() {
			const float s = glm::sin(rotation);
			const float c = glm::cos(rotation);
			glm::mat2 rotMatrix{ {c, s}, {-s, c} };

			glm::mat2 scaleMat{ {scale.x, .0f}, {.0f, scale.y} };
			return rotMatrix * scaleMat;
		} 
	};
	class GameEntity
	{
	public:
		using id_t = unsigned int;

		static GameEntity createGameEntity()
		{
			static id_t currentId = 0;
			return GameEntity(currentId++);
		}


		GameEntity(const GameEntity&) = delete;
		GameEntity& operator=(const GameEntity&) = delete;
		GameEntity(GameEntity&&) = default;
		GameEntity& operator=(GameEntity&&) = default;

		const id_t getId() { return id; }

		std::shared_ptr<EngineModel> model{};
		glm::vec3 color{};
		Transform2dComponent transform2d{};
	private:
		GameEntity(id_t ObjId) :id{ObjId} {}

		id_t id;

	};
}