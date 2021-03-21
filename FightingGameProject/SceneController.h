#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "ExperimentalLoader.h"

namespace RB
{
	class SceneController
	{
	private:
		ExperimentalLoader experimentalLoader;

	public:
		Scene* currentScene = nullptr;

		SceneController();
		~SceneController();

		void CreateScene(SceneType _sceneType);
	};
}