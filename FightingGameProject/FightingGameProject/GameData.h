#pragma once
#include "SceneType.h"

namespace RB
{
	class GameData
	{
	public:
		SceneType nextSceneType = SceneType::NONE;
		bool startGame = false;
		bool quitGame = false;
	};
}