#pragma once
#include "GameData.h"

namespace RB
{
	class GameDataFactory
	{
	private:
		GameData* _gameData = nullptr;

	public:
		~GameDataFactory()
		{
			delete _gameData;
		}

		void ResetGameData()
		{
			if (_gameData != nullptr)
			{
				delete _gameData;
			}

			_gameData = new GameData();
		}

		GameData* GetGameData()
		{
			return _gameData;
		}
	};
}