#pragma once
#include <stdint.h>
#include "olcPixelGameEngine.h"

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

		BoxCollider(olc::vi2d _pos, int32_t _width, int32_t _height, float _rotation)
		{
			pos = _pos;
			width = _width;
			height = _height;
			rotation = _rotation;

			SetQuad();
		}

		void UpdatePosition(bool left, bool right, bool up, bool down)
		{
			if (left && right || !left && !right)
			{

			}
			else if (left)
			{
				pos.x -= 1;
			}
			else if (right)
			{
				pos.x += 1;
			}

			if (up && down || !up && !down)
			{

			}
			else if (up)
			{
				pos.y -= 1;
			}
			else if (down)
			{
				pos.y += 1;
			}
		}

		void RotateCounterClockwise()
		{
			rotation -= 0.01f;
		}

		void RotateClockwise()
		{
			rotation += 0.01f;
		}

		void UpdateRotation()
		{
			for (int i = 0; i < quad.size(); i++)
			{
				float fX = ((float)quad[i].x * cosf(rotation)) - ((float)quad[i].y * sinf(rotation));
				float fY = ((float)quad[i].x * sinf(rotation)) + ((float)quad[i].y * cosf(rotation));

				rotatedQuad[i] = { (int32_t)std::round(fX), (int32_t)std::round(fY) };
			}
		}

		void SetQuad()
		{
			int32_t topLeftX = (int32_t)std::round(-(float)width / 2.0f);
			int32_t topLeftY = (int32_t)std::round(-(float)height / 2.0f);
			olc::vi2d topLeft = { topLeftX, topLeftY };
			olc::vi2d bottomLeft = topLeft + olc::vi2d{ 0, height };
			olc::vi2d topRight = topLeft + olc::vi2d{ width, 0 };
			olc::vi2d bottomRight = topLeft + olc::vi2d{ width, height };

			quad[0] = topLeft;
			quad[1] = bottomLeft;
			quad[2] = bottomRight;
			quad[3] = topRight;
		}

		void IncreaseWidth(int32_t _width)
		{
			width += _width;
		}

		void IncreaseHeight(int32_t _height)
		{
			height += _height;
		}
	};
}