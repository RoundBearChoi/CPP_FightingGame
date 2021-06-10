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
			olc::vi2d bottomLeft = (*_vec)[0]->objData.objBoxCollider.RelativePoint1() + (*_vec)[0]->objData.GetPosition();
			olc::vi2d bottomRight = (*_vec)[0]->objData.objBoxCollider.RelativePoint2() + (*_vec)[0]->objData.GetPosition();

			olc::vi2d prevBottomLeft = (*_vec)[0]->objData.objBoxCollider.RelativePoint1() + (*_vec)[0]->objData.GetPreviousPosition();
			olc::vi2d prevBottomRight = (*_vec)[0]->objData.objBoxCollider.RelativePoint2() + (*_vec)[0]->objData.GetPreviousPosition();

			if (bottomLeft != prevBottomLeft)
			{
				olc::vi2d screenPos_bottomLeft = ScreenVector::GetScreenPosition(bottomLeft, *_cam);
				olc::vi2d screenPos_prevBottomLeft = ScreenVector::GetScreenPosition(prevBottomLeft, *_cam);
				olc::Renderer::ptrPGE->DrawLine(screenPos_bottomLeft, screenPos_prevBottomLeft, olc::CYAN);
			}

			if (bottomRight != prevBottomRight)
			{
				olc::vi2d screenPos_bottomRight = ScreenVector::GetScreenPosition(bottomRight, *_cam);
				olc::vi2d screenPos_prevBottomRight = ScreenVector::GetScreenPosition(prevBottomRight, *_cam);
				olc::Renderer::ptrPGE->DrawLine(screenPos_bottomRight, screenPos_prevBottomRight, olc::CYAN);
			}
		}
	};
}