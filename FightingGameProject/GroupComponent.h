#pragma once

namespace RB
{
	class GameObj;
	class Camera;
	class GameData;

	class GroupComponent
	{
	public:
		virtual void UpdateComponent() {};
		virtual void UpdateComponent(GameObj& obj, GameData& gameData) {};

		virtual void RenderComponent() {};
		virtual void RenderComponent(GameObj* obj, Camera& cam) {};
	};
}