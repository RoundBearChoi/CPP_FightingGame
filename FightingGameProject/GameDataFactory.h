#pragma once
#include "InputData.h"

namespace RB
{
	class GameDataFactory
	{
	private:
		InputData* _gameData = nullptr;

	public:
		static GameDataFactory* ptr;

		~GameDataFactory();

		void ResetGameData();

		InputData* GetGameData();
	};
}