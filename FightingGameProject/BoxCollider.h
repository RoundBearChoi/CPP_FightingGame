#pragma once
#include <stdint.h>
#include "olcPixelGameEngine.h"
#include "Camera.h"
#include "ScreenVector.h"
#include "BoxRenderer.h"
#include "OffsetType.h"

namespace RB
{
	class BoxCollider
	{
	private:
		olc::vi2d relativePos = { 0, 0 };
		int32_t width = 0;
		int32_t height = 0;
		float rotation = 0.0f;

		std::array<olc::vi2d, 4> quad;
		std::array<olc::vi2d, 4> rotatedQuad;

	public:
		BoxCollider()
		{

		}

		olc::vi2d RelativePoint0() { return rotatedQuad[0] + relativePos; } //topleft
		olc::vi2d RelativePoint1() { return rotatedQuad[1] + relativePos; } //bottomleft
		olc::vi2d RelativePoint2() { return rotatedQuad[2] + relativePos; } //bottomright
		olc::vi2d RelativePoint3() { return rotatedQuad[3] + relativePos; } //topright

		olc::vi2d RelativePosition() { return relativePos; }
		void SetRelativePos(int32_t _x, int32_t _y) { relativePos.x = _x; relativePos.y = _y; }
		int32_t Width() { return width; }
		void SetWidth(int32_t _width) { width = _width; }
		int32_t Height() { return height; }
		void SetHeight(int32_t _height) { height = _height; }
		float Rotation() { return rotation; }
		void SetRotation(float _rotation) { rotation = _rotation; }
		void IncreaseWidth(int32_t _width) { width += _width; }
		void IncreaseHeight(int32_t _height) { height += _height; }
		void DecreaseWidth(int32_t _width) { width -= _width; }
		void DecreaseHeight(int32_t _height) { height -= _height; }

		BoxCollider(olc::vi2d _pos, int32_t _width, int32_t _height, float _rotation);
		void MovePosition(bool left, bool right, bool up, bool down);
		void RotateCounterClockwise();
		void RotateClockwise();
		void UpdateRotation();
		void SetQuad(OffsetType offsetType);
		void Render(Camera& cam, olc::vi2d playerPos, olc::Pixel _color);
	};
}