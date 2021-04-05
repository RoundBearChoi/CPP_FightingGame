#pragma once
#include "ObjData.h"
#include "StateController.h"
#include "ScreenVector.h"
#include "DevSettings.h"

namespace RB
{
	class GameObj
	{	
	public:
		ObjData objData;
		StateController stateController;

		GameObj();
		GameObj(size_t _creationID);
		~GameObj();

		void RenderPosition(Camera& cam);
		void RenderSpriteSize(Camera& cam);
		void RenderCollisionTiming(BodyType _bodyType, Camera& cam);
	};
}