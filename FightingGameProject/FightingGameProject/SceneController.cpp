#include "SceneController.h"
#include "FightScene.h"

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

			if (fighterDecals.GetSpriteCount() == 0)
			{
				fighterDecals.LoadSprites();
				fighterDecals.LoadDecals();

				currentScene->ptrDecalLoader = &fighterDecals;
			}
		}

		currentScene->InitScene();
	}
}