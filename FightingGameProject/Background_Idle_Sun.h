#pragma once
#include "State.h"
#include "FighterSpriteType.h"

namespace RB
{
	class Background_Idle_Sun : public State
	{
	private:
		const std::string path = "PNG files/Background/background_sun.png";

	public:
		size_t GetHash() override
		{
			static size_t hash = 0;

			if (hash == 0)
			{
				IF_COUT{ std::cout << "hashing: " << path << std::endl; }
				hash = std::hash<std::string>{}(path);
				IF_COUT{ std::cout << hash << std::endl; };
			}

			return hash;
		}

		void OnEnter(ObjData& objData, GameData& gameData) override
		{
			animationController.SetParams(SpriteType::BACKGROUND, 0 /*no need*/, 102, 82, 1, 1, 1);
			objData.SetSpriteSize({ 102, 82 });
		}

		void UpdateState(ObjData& objData, GameData& gameData) override
		{

		}
	};
}