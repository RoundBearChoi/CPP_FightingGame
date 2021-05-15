#pragma once
#include "GameData.h"

namespace RB
{
	class GameDataFactory
	{
	private:
		GameData* _gameData = nullptr;

	public:
		static GameDataFactory* ptr;

		~GameDataFactory();

		void ResetGameData();

		GameData* GetGameData();
	};
}