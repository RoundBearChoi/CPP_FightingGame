#include "SceneController.h"
#include "FightScene.h"
#include "HitBoxEditorScene.h"

namespace RB
{
	SceneController::SceneController()
	{
		IF_COUT{ std::cout << "constructing SceneController" << std::endl; };
	}

	SceneController::~SceneController()
	{
		IF_COUT{ std::cout << "destructing SceneController" << std::endl; };

		delete currentScene;
	}

	void SceneController::CreateScene(SceneType _sceneType)
	{
		delete currentScene;

		if (_sceneType == SceneType::FIGHT_SCENE)
		{
			currentScene = new FightScene();
		}
		else if (_sceneType == SceneType::BOXCOLLIDER_EDITOR)
		{
			currentScene = new HitBoxEditorScene();
		}

		experimentalLoader.LoadBackgroundSprites();
		experimentalLoader.Load_Fighter_0_Sprites();
		experimentalLoader.Load_Fighter_1_Sprites();
		experimentalLoader.LoadBoxColliderEditorSprites();

		SpriteLoader::ptr = &experimentalLoader;

		currentScene->InitScene();
	}
}