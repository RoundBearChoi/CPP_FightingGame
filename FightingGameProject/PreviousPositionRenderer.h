#pragma once
#include <vector>
#include "IGroupComponent.h"
#include "GameObj.h"

namespace RB
{
	class PreviousPositionRenderer : public IGroupComponent
	{
	private:
		std::vector<GameObj*>* _vec = nullptr;
		Camera* _cam = nullptr;

	public:
		PreviousPositionRenderer(std::vector<GameObj*>* targetVec, Camera* cam)
		{
			_vec = targetVec;
			_cam = cam;
		}

		void Update() override
		{
			DrawLines((*_vec)[0]);
			DrawLines((*_vec)[1]);
		}

		void DrawLines(GameObj* obj)
		{
			olc::vi2d bottomLeft = obj->objData.objBoxCollider.RelativePoint1() + obj->objData.GetPosition();
			olc::vi2d bottomRight = obj->objData.objBoxCollider.RelativePoint2() + obj->objData.GetPosition();

			olc::vi2d prevBottomLeft = obj->objData.objBoxCollider.RelativePoint1() + obj->objData.GetPreviousPosition();
			olc::vi2d prevBottomRight = obj->objData.objBoxCollider.RelativePoint2() + obj->objData.GetPreviousPosition();

			if (bottomLeft != prevBottomLeft)
			{
				olc::vi2d screenPos_bottomLeft = ScreenVector::GetScreenPosition(bottomLeft, *_cam);
				olc::vi2d screenPos_prevBottomLeft = ScreenVector::GetScreenPosition(prevBottomLeft, *_cam);

				olc::vi2d dir = screenPos_prevBottomLeft - screenPos_bottomLeft;
				olc::vi2d normDir = dir.norm();

				olc::Renderer::ptrPGE->DrawLine(screenPos_bottomLeft + (dir * 5), screenPos_bottomLeft - (dir * 5), olc::CYAN);
			}

			if (bottomRight != prevBottomRight)
			{
				olc::vi2d screenPos_bottomRight = ScreenVector::GetScreenPosition(bottomRight, *_cam);
				olc::vi2d screenPos_prevBottomRight = ScreenVector::GetScreenPosition(prevBottomRight, *_cam);

				olc::vi2d dir = screenPos_prevBottomRight - screenPos_bottomRight;
				olc::vi2d normDir = dir.norm();

				olc::Renderer::ptrPGE->DrawLine(screenPos_bottomRight + (dir * 5), screenPos_bottomRight - (dir * 5), olc::CYAN);
			}
		}
	};
}