#pragma once
#include "GameDataFactory.h"
#include "StateFactory.h"
#include "Camera.h"
#include "DevSettings.h"
#include "ScreenVector.h"
#include "SceneType.h"

namespace RB
{
	class Scene
	{
	protected:
		GameDataFactory* _gameDataFactory = nullptr;
		StateFactory* _stateFactory = nullptr;

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