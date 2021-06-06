#include "GameDataFactory.h"

namespace RB
{
	GameDataFactory* GameDataFactory::ptr = nullptr;

	GameDataFactory::~GameDataFactory()
	{
		delete _gameData;
	}

	void GameDataFactory::ResetGameData()
	{
		if (_gameData != nullptr)
		{
			delete _gameData;
		}

		_gameData = new InputData();
	}

	InputData* GameDataFactory::GetGameData()
	{
		return _gameData;
	}
}