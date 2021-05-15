#pragma once
#include "Camera.h"
#include "DevSettings.h"
#include "ScreenVector.h"
#include "SceneType.h"

namespace RB
{
	class Scene
	{
	public:
		Camera* _cam = nullptr;
		SceneType sceneType = SceneType::NONE;

		virtual void InitScene() = 0;
		virtual void UpdateScene() = 0;
		virtual void RenderObjs() = 0;
		virtual void RenderStates(bool update) = 0;

		virtual ~Scene();

		void RenderCenterMark(Camera& cam);
	};
}