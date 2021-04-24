#include "BoxCollider.h"

namespace RB
{
	BoxCollider::BoxCollider(olc::vi2d _pos, int32_t _width, int32_t _height, float _rotation)
	{
		relativePos = _pos;
		width = _width;
		height = _height;
		rotation = _rotation;

		SetQuad(OffsetType::CENTER_CENTER);
	}

	void BoxCollider::MovePosition(bool left, bool right, bool up, bool down)
	{
		if (left && right || !left && !right)
		{

		}
		else if (left)
		{
			relativePos.x -= 1;
		}
		else if (right)
		{
			relativePos.x += 1;
		}

		if (up && down || !up && !down)
		{

		}
		else if (up)
		{
			relativePos.y -= 1;
		}
		else if (down)
		{
			relativePos.y += 1;
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

	void BoxCollider::SetQuad(OffsetType offsetType)
	{
		int32_t topLeftX = 0;
		int32_t topLeftY = 0;

		if (offsetType == OffsetType::CENTER_CENTER)
		{
			topLeftX = (int32_t)std::round(-(float)width / 2.0f);
			topLeftY = (int32_t)std::round(-(float)height / 2.0f);
		}
		else if (offsetType == OffsetType::BOTTOM_CENTER)
		{
			topLeftX = (int32_t)std::round(-(float)width / 2.0f);
			topLeftY = (int32_t)std::round(-(float)height);
		}

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
		quad[0] = ScreenVector::GetScreenPosition(RelativePoint0() + playerPos, cam);
		quad[1] = ScreenVector::GetScreenPosition(RelativePoint1() + playerPos, cam);
		quad[2] = ScreenVector::GetScreenPosition(RelativePoint2() + playerPos, cam);
		quad[3] = ScreenVector::GetScreenPosition(RelativePoint3() + playerPos, cam);

		if (_color == olc::RED)
		{
			std::array<olc::vf2d, 4> floats;
			floats[0] = quad[0];
			floats[1] = quad[1];
			floats[2] = quad[2];
			floats[3] = quad[3];

			BoxRenderer::Render(floats, _color);
		}

		if (DevSettings::renderMode == RenderMode::DEBUG_ONLY || DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG)
		{
			olc::Renderer::ptrPGE->DrawLine(quad[0], quad[1], _color);
			olc::Renderer::ptrPGE->DrawLine(quad[1], quad[2], _color);
			olc::Renderer::ptrPGE->DrawLine(quad[2], quad[3], _color);
			olc::Renderer::ptrPGE->DrawLine(quad[3], quad[0], _color);
		}
	}
}