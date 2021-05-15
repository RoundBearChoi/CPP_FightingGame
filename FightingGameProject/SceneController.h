#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "GameDataFactory.h"
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

	public:
		SceneController(GameDataFactory* gameDataFactory)
		{
			_gameDataFactory = gameDataFactory;
		}

		Scene* currentScene = nullptr;

		SceneController();
		~SceneController();

		void CreateScene(SceneType _sceneType);
		void ChangeScene();
		void Load();
	};
}