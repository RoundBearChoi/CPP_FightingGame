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
		std::vector<Scene> vecScenes;

	public:
		SceneController()
		{
			vecScenes.reserve(1);
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

				vecScenes.push_back(FightScene());
			}
		
			vecScenes[0].InitScene();
		}
		
		void UpdateCurrentScene(olc::PixelGameEngine* ptrEngine, GameData& gameData)
		{
			vecScenes[0].UpdateScene(ptrEngine, gameData);
		}
		
		void RenderCurrentScene(bool update, olc::PixelGameEngine* ptrEngine)
		{
			vecScenes[0].RenderObjs(ptrEngine);
			vecScenes[0].RenderStates(update, ptrEngine);
		}
	};
}