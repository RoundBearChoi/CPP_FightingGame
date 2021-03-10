#pragma once
#include "Scene.h"
#include "DevSettings.h"
#include "SceneType.h"

//concreate decal paths
#include "FighterDecals.h"

//concrete scenes
#include "FightScene.h"

namespace RB
{
	class SceneController
	{
	private:
		FighterDecals fighterDecals;

	public:
		Scene* currentScene = nullptr;

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
					fighterDecals.LoadSprites();
					fighterDecals.LoadDecals();

					currentScene->ptrDecalLoader = &fighterDecals;
				}
			}

			currentScene->InitScene();
		}
	};
}