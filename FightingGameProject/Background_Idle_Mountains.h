#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Background_Idle_Mountains : public State
	{
	private:
		const std::string path = "PNG files\\Background\\background_mountains.png";

	public:
		size_t GetHash() override
		{
			static size_t hash = 0;

			if (hash == 0)
			{
				hash = std::hash<std::string>{}(path);
				IF_COUT{ std::cout << "mountains hash: " << hash << std::endl; }
			}

			return hash;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams(SpriteType::BACKGROUND, 0 /*no need*/, 1700, 300, 1, 1, 1);
			objData.SetSpriteSize({ 1700, 300 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}