#pragma once
#include "ObjData.h"
#include "StateController.h"
#include "RelativeVector.h"
#include "DevSettings.h"
#include "Renderer.h"

namespace RB
{
	class GameObj
	{	
	public:
		ObjData objData;
		StateController stateController;

		GameObj();
		~GameObj();

		void RenderPosition(Camera& cam);
		void RenderSpriteSize(Camera& cam);
		void RenderCollisionTiming(BodyType _bodyType, Camera& cam);
	};
}