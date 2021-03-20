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

			IF_COUT{ std::cout << "mountain initial hash: " << hash << std::endl; }

			if (hash == 0)
			{
				IF_COUT{ std::cout << "hashing: " << path << std::endl; }
				hash = std::hash<std::string>{}(path);
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