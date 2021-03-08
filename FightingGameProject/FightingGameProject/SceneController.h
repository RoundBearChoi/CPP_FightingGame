#pragma once
#include "Scene.h"
#include "DevSettings.h"
#include "SceneType.h"

//concrete scenes
#include "FightScene.h"

namespace RB
{
	class SceneController
	{
	private:
		Scene* currentScene = nullptr;

	public:
		SceneController()
		{
			IF_COUT{ std::cout << "constructing SceneController" << std::endl; }
		}

		~SceneController()
		{
			IF_COUT{ std::cout << "destructing SceneController" << std::endl; }

			delete currentScene;
		}

		void CreateScene(SceneType _sceneType)
		{
			delete currentScene;

			if (_sceneType == SceneType::FIGHT_SCENE)
			{
				//if (titleSceneDecalLoader.GetSpriteCount() == 0)
				//{
				//	titleSceneDecalLoader.LoadSprites<TitleDecalPath>();
				//	titleSceneDecalLoader.LoadDecals();
				//}

				currentScene = new FightScene(/*&titleSceneDecalLoader*/);
			}

			currentScene->InitScene();
		}

		void UpdateCurrentScene(olc::PixelGameEngine* ptrEngine, GameData& gameData)
		{
			currentScene->UpdateScene(ptrEngine, gameData);
		}

		void RenderCurrentScene(bool update, olc::PixelGameEngine* ptrEngine)
		{
			currentScene->RenderObjs(ptrEngine);
			currentScene->RenderStates(update, ptrEngine);
		}
	};
}