#pragma once
#include "GameData.h"
#include "Camera.h"
#include "DevSettings.h"
#include "ScreenVector.h"
#include "SceneType.h"

namespace RB
{
	class Scene
	{
	public:
		Camera cam;
		SceneType sceneType = SceneType::NONE;

		virtual void InitScene() = 0;
		virtual void UpdateScene(GameData& gameData) = 0;
		virtual void RenderObjs() = 0;
		virtual void RenderStates(bool update) = 0;

		virtual ~Scene();

		void RenderCenterMark(Camera& cam);
	};
}