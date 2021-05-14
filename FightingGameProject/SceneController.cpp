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
			currentScene = new FightScene(_gameDataFactory, _stateFactory);
			currentScene->sceneType = _sceneType;
		}
		else if (_sceneType == SceneType::BOXCOLLIDER_EDITOR)
		{
			currentScene = new HitBoxEditorScene(_gameDataFactory, _stateFactory);
			currentScene->sceneType = _sceneType;
		}

		currentScene->InitScene();
	}

	void SceneController::ChangeScene()
	{
		GameData& gameData = *_gameDataFactory->GetGameData();

		if (gameData.key_f11)
		{
			if (currentScene->sceneType == SceneType::FIGHT_SCENE)
			{
				CreateScene(SceneType::BOXCOLLIDER_EDITOR);
			}
			else if (currentScene->sceneType == SceneType::BOXCOLLIDER_EDITOR)
			{
				CreateScene(SceneType::FIGHT_SCENE);
			}

			IF_COUT{ std::cout << "f11 pressed" << std::endl; };
			gameData.key_f11->processed = true;
		}
	}

	void SceneController::Load()
	{
		spriteLoader.Load_Fighter_0_Sprites();
		spriteLoader.Load_Fighter_1_Sprites();
		spriteLoader.LoadBoxColliderEditorSprites();
		spriteLoader.LoadDebugElementSprites();
		spriteLoader.LoadInputBufferSprites();
		spriteLoader.LoadProjectileSprites();
		spriteLoader.LoadImpactEffectSprites();

		SpriteLoader::ptr = &spriteLoader;
	}
}