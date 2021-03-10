#pragma once
#include "Scene.h"
#include "DevSettings.h"
#include "SceneType.h"

//concreate decal paths
#include "FighterDecalPath.h"

//concrete scenes
#include "FightScene.h"
#include "DecalLoader.h"

namespace RB
{
	class SceneController
	{
	private:
		Scene* currentScene = nullptr;
		DecalLoader fighterDecals;

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
				currentScene = new FightScene();

				if (fighterDecals.GetSpriteCount() == 0)
				{
					fighterDecals.LoadSprites<FighterDecalPath>();
					fighterDecals.LoadDecals();

					currentScene->ptrDecalLoader = &fighterDecals;
				}
			}
		
			currentScene->InitScene();
		}
		
		void UpdateCurrentScene(GameData& gameData)
		{
			currentScene->UpdateScene(gameData);
		}
		
		void RenderCurrentScene(olc::PixelGameEngine* ptrEngine, bool update)
		{
			currentScene->RenderObjPosition(ptrEngine);
			currentScene->RenderStates(update, ptrEngine);
		}
	};
}