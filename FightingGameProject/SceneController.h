#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "SpriteLoader.h"
#include "FightScene.h"
#include "HitBoxEditorScene.h"

namespace RB
{
	class SceneController
	{
	private:
		SpriteLoader spriteLoader;

	public:
		SceneController();
		~SceneController();

		Scene* currentScene = nullptr;

		void CreateScene(SceneType _sceneType);
		void ChangeScene();
		void Load();
	};
}