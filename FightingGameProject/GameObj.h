#pragma once
#include "ObjData.h"
#include "StateController.h"
#include "ScreenVector.h"
#include "DevSettings.h"
#include "StateFactory.h"

namespace RB
{
	class GameObj
	{
	private:
		StateFactory* _stateFactory = nullptr;

	public:
		ObjData objData;
		StateController* stateController = nullptr;

		GameObj(StateFactory* stateFactory);
		~GameObj();

		void RenderPosition(Camera& cam);
		void RenderSpriteSize(Camera& cam);
		void RenderCollisionTiming(BodyType _bodyType, Camera& cam);
	};
}