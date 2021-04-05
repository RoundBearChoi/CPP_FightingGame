#include "BoxCollider.h"

namespace RB
{
	BoxCollider::BoxCollider(olc::vi2d _pos, int32_t _width, int32_t _height, float _rotation)
	{
		pos = _pos;
		width = _width;
		height = _height;
		rotation = _rotation;

		SetQuad();
	}

	void BoxCollider::MovePosition(bool left, bool right, bool up, bool down)
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

	void BoxCollider::RotateCounterClockwise()
	{
		rotation -= 0.01f;
	}

	void BoxCollider::RotateClockwise()
	{
		rotation += 0.01f;
	}

	void BoxCollider::UpdateRotation()
	{
		for (int i = 0; i < quad.size(); i++)
		{
			float fX = ((float)quad[i].x * cosf(rotation)) - ((float)quad[i].y * sinf(rotation));
			float fY = ((float)quad[i].x * sinf(rotation)) + ((float)quad[i].y * cosf(rotation));

			rotatedQuad[i] = { (int32_t)std::round(fX), (int32_t)std::round(fY) };
		}
	}

	void BoxCollider::SetQuad()
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

	void BoxCollider::Render(Camera& cam, olc::vi2d playerPos, olc::Pixel _color)
	{
		std::array<olc::vi2d, 4> quad;
		quad[0] = ScreenVector::GetScreenPosition(Point0() + playerPos, cam);
		quad[1] = ScreenVector::GetScreenPosition(Point1() + playerPos, cam);
		quad[2] = ScreenVector::GetScreenPosition(Point2() + playerPos, cam);
		quad[3] = ScreenVector::GetScreenPosition(Point3() + playerPos, cam);

		if (_color == olc::RED)
		{
			std::array<olc::vf2d, 4> floats;
			floats[0] = quad[0];
			floats[1] = quad[1];
			floats[2] = quad[2];
			floats[3] = quad[3];

			DebugRenderer::RenderBox(floats);
		}

		olc::Renderer::ptrPGE->DrawLine(quad[0], quad[1], _color);
		olc::Renderer::ptrPGE->DrawLine(quad[1], quad[2], _color);
		olc::Renderer::ptrPGE->DrawLine(quad[2], quad[3], _color);
		olc::Renderer::ptrPGE->DrawLine(quad[3], quad[0], _color);
	}
}