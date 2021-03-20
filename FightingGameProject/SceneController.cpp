#include "SceneController.h"
#include "FightScene.h"
#include "HitBoxEditorScene.h"

namespace RB
{
	SceneController::SceneController()
	{
		IF_COUT{ std::cout << "constructing SceneController" << std::endl; }
	}

	SceneController::~SceneController()
	{
		IF_COUT{ std::cout << "destructing SceneController" << std::endl; }

		delete currentScene;
	}

	void SceneController::CreateScene(SceneType _sceneType)
	{
		delete currentScene;

		if (_sceneType == SceneType::FIGHT_SCENE)
		{
			currentScene = new FightScene();
		}
		else if (_sceneType == SceneType::HITBOX_EDITOR_SCENE)
		{
			currentScene = new HitBoxEditorScene();
		}

		if (fighterDecals.GetSpriteCount() == 0)
		{
			fighterDecals.LoadSprites();
			fighterDecals.LoadDecals();

			currentScene->ptrDecalLoader = &fighterDecals;
		}

		experimentalLoader.LoadBackgroundSprites();

		currentScene->InitScene();
	}
}