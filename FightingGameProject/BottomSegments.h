#pragma once
#include <array>
#include "olcPixelGameEngine.h"
#include "ObjData.h"
#include "BoxCollider.h"

namespace RB
{
	class MoveSegments
	{
	private:
		std::array<olc::vi2d, 2> _vecBottomSegment_left = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };
		std::array<olc::vi2d, 2> _vecBottomSegment_right = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };

		std::array<olc::vi2d, 2> _vecTopSegment_left = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };
		std::array<olc::vi2d, 2> _vecTopSegment_right = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };

		ObjData* _objData;
		BoxCollider* _objBoxCollider = nullptr;
		//olc::vi2d* _currentPosition = nullptr;
		//olc::vi2d* _previousPosition = nullptr;

	public:
		MoveSegments(ObjData* objData, BoxCollider* objBoxCollider)
		{
			_objData = objData;
			_objBoxCollider = objBoxCollider;
		}

		void SetSegments()
		{
			//start with default 0
			_vecBottomSegment_left = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };
			_vecBottomSegment_right = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };
			_vecTopSegment_left = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };
			_vecTopSegment_right = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };

			//set new segments
			olc::vi2d bottomLeft = _objBoxCollider->RelativePoint1() + _objData->GetPosition();
			olc::vi2d bottomRight = _objBoxCollider->RelativePoint2() + _objData->GetPosition();
			
			olc::vi2d prevBottomLeft = _objBoxCollider->RelativePoint1() + _objData->GetPreviousPosition();
			olc::vi2d prevBottomRight = _objBoxCollider->RelativePoint2() + _objData->GetPreviousPosition();

			olc::vi2d topLeft = _objBoxCollider->RelativePoint0() + _objData->GetPosition();
			olc::vi2d topRight = _objBoxCollider->RelativePoint3() + _objData->GetPosition();

			olc::vi2d prevTopLeft = _objBoxCollider->RelativePoint0() + _objData->GetPreviousPosition();
			olc::vi2d prevTopRight = _objBoxCollider->RelativePoint3() + _objData->GetPreviousPosition();
			
			if (bottomLeft != prevBottomLeft)
			{
				olc::vi2d dir = prevBottomLeft - bottomLeft;
				_vecBottomSegment_left[0] = bottomLeft + (dir * 5);
				_vecBottomSegment_left[1] = bottomLeft - (dir * 5);
			}
			
			if (bottomRight != prevBottomRight)
			{
				olc::vi2d dir = prevBottomRight - bottomRight;
				_vecBottomSegment_right[0] = bottomRight + (dir * 5);
				_vecBottomSegment_right[1] = bottomRight - (dir * 5);
			}

			if (topLeft != prevTopLeft)
			{
				olc::vi2d dir = prevTopLeft - topLeft;
				_vecTopSegment_left[0] = topLeft + (dir * 5);
				_vecTopSegment_left[1] = topLeft - (dir * 5);
			}

			if (topRight != prevTopRight)
			{
				olc::vi2d dir = prevTopRight - topRight;
				_vecTopSegment_right[0] = topRight + (dir * 5);
				_vecTopSegment_right[1] = topRight - (dir * 5);
			}
		}

		std::array<olc::vi2d, 2> GetBottomLeftSegment()
		{
			return _vecBottomSegment_left;
		}

		std::array<olc::vi2d, 2> GetBottomRightSegment()
		{
			return _vecBottomSegment_right;
		}

		std::array<olc::vi2d, 2> GetTopLeftSegment()
		{
			return _vecTopSegment_left;
		}

		std::array<olc::vi2d, 2> GetTopRightSegment()
		{
			return _vecTopSegment_right;
		}
	};
}