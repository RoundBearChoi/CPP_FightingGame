#pragma once
#include "GameData.h"
#include "Camera.h"
#include "DecalLoader.h"

namespace RB
{
	class Scene
	{
	public:
		DecalLoader* ptrDecalLoader;
		Camera cam;

		virtual void InitScene() = 0;
		virtual void Update(GameData& gameData) = 0;
		virtual void RenderObjPosition() = 0;
		virtual void RenderStates(bool update) = 0;

		virtual ~Scene();

		void RenderCenterMark(Camera& cam);
	};
}