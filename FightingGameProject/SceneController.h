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
		SpriteLoader experimentalLoader;

	public:
		Scene* currentScene = nullptr;

		SceneController();
		~SceneController();

		void CreateScene(SceneType _sceneType);
	};
}