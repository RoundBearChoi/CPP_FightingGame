#pragma once
#include "olcPixelGameEngine.h"
#include "DevSettings.h"
#include "ObjData.h"

namespace RB
{
	class GameObj
	{	
	public:
		ObjData objData;

		GameObj()
		{
			IF_COUT{ std::cout << "construcing GameObj: " << objData.GetCreationID() << std::endl; }
		}

		~GameObj()
		{
			IF_COUT{ std::cout << "destructing GameObj: " << objData.GetCreationID() << std::endl; }
		}

		void RenderPosition(olc::PixelGameEngine* ptrEngine, olc::vi2d& camPos)
		{
			ptrEngine->FillCircle(objData.GetPosition() + camPos, 2, olc::RED);
		}

		void RenderSpriteSize(olc::PixelGameEngine* ptrEngine, olc::vi2d& camPos)
		{
			int32_t halfWidth = objData.GetSpriteSize().x / 2;
			int32_t height = objData.GetSpriteSize().y;

			olc::vi2d leftTop = { objData.GetPosition().x - halfWidth, objData.GetPosition().y - height };
			
			ptrEngine->DrawRect(leftTop.x + camPos.x, leftTop.y + camPos.y, objData.GetSpriteSize().x, objData.GetSpriteSize().y);
		}
	};
}