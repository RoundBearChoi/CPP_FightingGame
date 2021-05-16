#pragma once
#include "IGroupComponent.h"

namespace RB
{
	class FighterJump : public IGroupComponent
	{
	private:
		std::vector<GameObj*>* _vecFighters = nullptr;

	public:
		FighterJump(std::vector<GameObj*>* vecFighters)
		{
			_vecFighters = vecFighters;
		}

		void Update() override
		{
			std::vector<GameObj*>& vec = *_vecFighters;

			for (size_t i = 0; i < vec.size(); i++)
			{
				ProcessJump(*vec[i]);
			}
		}

		void ProcessJump(GameObj& obj)
		{
			//process jump
			if (obj.objData.ptrJumpProcessor != nullptr)
			{
				PlayerInput p = PlayerInput::Get(obj.objData.GetPlayerType());
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