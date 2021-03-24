#include "SceneController.h"

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

		spriteLoader.LoadBackgroundSprites();
		spriteLoader.Load_Fighter_0_Sprites();
		spriteLoader.Load_Fighter_1_Sprites();
		spriteLoader.LoadBoxColliderEditorSprites();
		spriteLoader.LoadDebugElements();

		SpriteLoader::ptr = &spriteLoader;

		currentScene->InitScene();
	}
}