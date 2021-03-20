#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "FighterDecals.h"
#include "ExperimentalLoader.h"

namespace RB
{
	class SceneController
	{
	private:
		FighterDecals fighterDecals;
		ExperimentalLoader experimentalLoader;

	public:
		Scene* currentScene = nullptr;

		SceneController();
		~SceneController();

		void CreateScene(SceneType _sceneType);
	};
}