#pragma once
#include <array>
#include "olcPixelGameEngine.h"
#include "BoxCollider.h"

namespace RB
{

	class BottomSegments
	{
	private:
		std::array<olc::vi2d, 2> _vecBottomSegment_left = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };
		std::array<olc::vi2d, 2> _vecBottomSegment_right = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };
		BoxCollider* _objBoxCollider = nullptr;
		olc::vi2d* _currentPosition = nullptr;
		olc::vi2d* _previousPosition = nullptr;

	public:
		BottomSegments(olc::vi2d* currentPos, olc::vi2d* prevPos, BoxCollider* objBoxCollider)
		{
			_currentPosition = currentPos;
			_previousPosition = prevPos;
			_objBoxCollider = objBoxCollider;
		}

		void SetSegments()
		{
			//start with default 0
			_vecBottomSegment_left = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };
			_vecBottomSegment_right = { olc::vi2d{0, 0}, olc::vi2d{0, 0} };

			//set new segments
			olc::vi2d bottomLeft = _objBoxCollider->RelativePoint1() + *_currentPosition;
			olc::vi2d bottomRight = _objBoxCollider->RelativePoint2() + *_currentPosition;
			
			olc::vi2d prevBottomLeft = _objBoxCollider->RelativePoint1() + *_previousPosition;
			olc::vi2d prevBottomRight = _objBoxCollider->RelativePoint2() + *_previousPosition;
			
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
		}

		std::array<olc::vi2d, 2> GetBottomLeftSegment()
		{
			return _vecBottomSegment_left;
		}

		std::array<olc::vi2d, 2> GetBottomRightSegment()
		{
			return _vecBottomSegment_right;
		}
	};
}