#pragma once
#include "GameData.h"
#include "Camera.h"
#include "DevSettings.h"
#include "RelativeVector.h"
#include "Renderer.h"

namespace RB
{
	class Scene
	{
	public:
		Camera cam;

		virtual void InitScene() = 0;
		virtual void Update(GameData& gameData) = 0;
		virtual void RenderObjs() = 0;
		virtual void RenderStates(bool update) = 0;

		virtual ~Scene();

		void RenderCenterMark(Camera& cam);
	};
}