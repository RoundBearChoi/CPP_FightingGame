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
			std::array<olc::vi2d, 2> bottomLeft = obj->objData.bottomSegments.GetBottomLeftSegment();
			std::array<olc::vi2d, 2> bottomRight = obj->objData.bottomSegments.GetBottomRightSegment();

			if (bottomLeft[0] != olc::vi2d{ 0 , 0 } || bottomLeft[1] != olc::vi2d{ 0 , 0 })
			{
				olc::vi2d left0 = ScreenVector::GetScreenPosition(bottomLeft[0], *_cam);
				olc::vi2d left1 = ScreenVector::GetScreenPosition(bottomLeft[1], *_cam);
				olc::Renderer::ptrPGE->DrawLine(left0, left1, olc::CYAN);
			}

			if (bottomRight[0] != olc::vi2d{ 0 , 0 } || bottomRight[1] != olc::vi2d{ 0 , 0 })
			{
				olc::vi2d right0 = ScreenVector::GetScreenPosition(bottomRight[0], *_cam);
				olc::vi2d right1 = ScreenVector::GetScreenPosition(bottomRight[1], *_cam);
				olc::Renderer::ptrPGE->DrawLine(right0, right1, olc::CYAN);
			}
		}
	};
}