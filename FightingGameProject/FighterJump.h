#pragma once
#include "GameObj.h"
#include "GameData.h"

namespace RB
{
	class FighterJump
	{
	public:
		void Update(GameObj& obj, GameData& gameData)
		{
			//process jump
			if (obj.objData.ptrJumpProcessor != nullptr)
			{
				PlayerInput p = PlayerInput::Get(obj.objData.GetPlayerType(), gameData);
				Directions d = Directions::Get(obj.objData.IsFacingRight(), p);
				obj.objData.ptrJumpProcessor->UpdateJump(d.up, d.forward, d.back);

				if (obj.objData.GetPosition().y <= 0)
				{
					olc::vi2d vertical = obj.objData.GetPosition() - olc::vi2d(0, obj.objData.ptrJumpProcessor->GetUpForce());
					obj.objData.SetPosition(vertical);

					olc::vi2d horizontalForce = olc::vi2d{ 0, 0 };

					if (obj.objData.IsFacingRight())
					{
						horizontalForce = olc::vi2d(obj.objData.ptrJumpProcessor->GetSideForce(), 0);
					}
					else
					{
						horizontalForce = olc::vi2d(obj.objData.ptrJumpProcessor->GetSideForce() * -1, 0);
					}

					if (!obj.objData.ptrJumpProcessor->moveBack)
					{
						olc::vi2d horizontal = obj.objData.GetPosition() + horizontalForce;
						obj.objData.SetPosition(horizontal);
					}
					else
					{
						olc::vi2d horizontal = obj.objData.GetPosition() - horizontalForce;
						obj.objData.SetPosition(horizontal);
					}
				}
			}

			//clear jump
			if (obj.objData.GetPosition().y > 0)
			{
				olc::vi2d groundPos = olc::vi2d(obj.objData.GetPosition().x, 0);
				obj.objData.SetPosition(groundPos);

				delete obj.objData.ptrJumpProcessor;
				obj.objData.ptrJumpProcessor = nullptr;
			}
		}
	};
}