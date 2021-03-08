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
		Scene currentScene;

	public:
		SceneController()
		{
			IF_COUT{ std::cout << "constructing SceneController" << std::endl; }
		}

		~SceneController()
		{
			IF_COUT{ std::cout << "destructing SceneController" << std::endl; }
		}

		void CreateScene(SceneType _sceneType)
		{
			if (_sceneType == SceneType::FIGHT_SCENE)
			{
				//if (titleSceneDecalLoader.GetSpriteCount() == 0)
				//{
				//	titleSceneDecalLoader.LoadSprites<TitleDecalPath>();
				//	titleSceneDecalLoader.LoadDecals();
				//}

				FightScene fightScene(1);

				currentScene = fightScene;
			}
		
			currentScene.InitScene();
		}
		
		void UpdateCurrentScene(olc::PixelGameEngine* ptrEngine, GameData& gameData)
		{
			currentScene.UpdateScene(ptrEngine, gameData);
		}
		
		void RenderCurrentScene(bool update, olc::PixelGameEngine* ptrEngine)
		{
			currentScene.RenderObjPosition(ptrEngine);
			currentScene.RenderStates(update, ptrEngine);
		}
	};
}