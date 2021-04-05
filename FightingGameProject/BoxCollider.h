#pragma once
#include <stdint.h>
#include "olcPixelGameEngine.h"
#include "Camera.h"
#include "ScreenVector.h"
#include "DebugRenderer.h"

namespace RB
{
	class BoxCollider
	{
	private:
		olc::vi2d pos = { 0, 0 };
		int32_t width = 0;
		int32_t height = 0;
		float rotation = 0.0f;

		std::array<olc::vi2d, 4> quad;
		std::array<olc::vi2d, 4> rotatedQuad;

	public:
		BoxCollider()
		{

		}

		olc::vi2d Point0() { return rotatedQuad[0] + pos; } //topleft
		olc::vi2d Point1() { return rotatedQuad[1] + pos; } //bottomleft
		olc::vi2d Point2() { return rotatedQuad[2] + pos; } //bottomright
		olc::vi2d Point3() { return rotatedQuad[3] + pos; } // topright

		olc::vi2d Position() { return pos; }
		void SetPosition(int32_t _x, int32_t _y) { pos.x = _x; pos.y = _y; }
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
		void SetQuad();
		void Render(Camera& cam, olc::vi2d playerPos, olc::Pixel _color);
	};
}