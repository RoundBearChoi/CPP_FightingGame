#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "SpriteLoader.h"
#include "FightScene.h"
#include "HitBoxEditorScene.h"
#include "GameData.h"

namespace RB
{
	class SceneController
	{
	private:
		SpriteLoader spriteLoader;

	public:
		Scene* currentScene = nullptr;

		SceneController();
		~SceneController();

		void CreateScene(SceneType _sceneType);
		void ChangeScene(GameData& gameData);
		void Load();
	};
}