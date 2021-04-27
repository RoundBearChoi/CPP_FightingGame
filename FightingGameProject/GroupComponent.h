#pragma once

namespace RB
{
	class GameObj;
	class Camera;
	class GameData;

	class GroupComponent
	{
	public:
		virtual void Update() {}
		virtual void Update(GameObj& obj) {}
		virtual void Update(GameObj& obj, GameData& gameData) {}
		virtual void Update(GameObj& obj, Camera& cam) {}
		//virtual void Update(std::array<GameObj, 2>& arrObjs) {}
		virtual void Update(std::vector<GameObj*>& vecObjs) {}
	};
}