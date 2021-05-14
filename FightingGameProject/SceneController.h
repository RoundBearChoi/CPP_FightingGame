#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "GameDataFactory.h"
#include "StateFactory.h"
#include "SpriteLoader.h"
#include "FightScene.h"
#include "HitBoxEditorScene.h"

namespace RB
{
	class SceneController
	{
	private:
		SpriteLoader spriteLoader;
		GameDataFactory* _gameDataFactory = nullptr;
		StateFactory* _stateFactory = nullptr;

	public:
		SceneController(GameDataFactory* gameDataFactory, StateFactory* stateFactory)
		{
			_gameDataFactory = gameDataFactory;
			_stateFactory = stateFactory;
		}

		Scene* currentScene = nullptr;

		SceneController();
		~SceneController();

		void CreateScene(SceneType _sceneType);
		void ChangeScene();
		void Load();
	};
}