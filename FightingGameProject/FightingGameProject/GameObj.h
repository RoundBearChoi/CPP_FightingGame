#pragma once
#include "olcPixelGameEngine.h"
#include "DevSettings.h"
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

		GameObj()
		{
			IF_COUT{ std::cout << "construcing GameObj: " << objData.GetCreationID() << std::endl; }
		}

		~GameObj()
		{
			IF_COUT{ std::cout << "destructing GameObj: " << objData.GetCreationID() << std::endl; }
		}

		void RenderPosition(olc::PixelGameEngine* ptrEngine, const olc::vi2d& camPos, const float& zoomScale)
		{
			olc::vi2d relative = RelativeVector::Get(objData.GetPosition(), camPos, zoomScale);

			ptrEngine->FillCircle(relative, 2, olc::RED);
		}

		void RenderSpriteSize(olc::PixelGameEngine* ptrEngine, const olc::vi2d& camPos, const float& zoomScale)
		{
			int32_t halfWidth = objData.GetSpriteSize().x / 2;
			int32_t height = objData.GetSpriteSize().y;
			olc::vi2d leftTop = { objData.GetPosition().x - halfWidth, objData.GetPosition().y - height };
			
			olc::vi2d relativePos = RelativeVector::Get(leftTop, camPos, zoomScale);
			olc::vi2d relativeSize = RelativeVector::Get(objData.GetSpriteSize(), zoomScale);
			
			ptrEngine->DrawRect(relativePos.x, relativePos.y, relativeSize.x, relativeSize.y);
		}
	};
}