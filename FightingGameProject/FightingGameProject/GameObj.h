#pragma once
#include "olcPixelGameEngine.h"
#include "ObjData.h"
#include "StateController.h"
#include "RelativeVector.h"

namespace RB
{
	class GameObj
	{	
	public:
		ObjData objData;
		StateController stateController;

		GameObj();
		~GameObj();

		void RenderPosition(olc::PixelGameEngine* ptrEngine, Camera& cam);
		void RenderSpriteSize(olc::PixelGameEngine* ptrEngine, Camera& cam);
	};
}