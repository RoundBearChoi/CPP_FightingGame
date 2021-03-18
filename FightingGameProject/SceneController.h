#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "FighterDecals.h"

namespace RB
{
	class SceneController
	{
	private:
		FighterDecals fighterDecals;

	public:
		Scene* currentScene = nullptr;

		SceneController();
		~SceneController();

		void CreateScene(SceneType _sceneType);
	};
}