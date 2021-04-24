#pragma once
#include "GroupComponent.h"
#include "UIElement.h"
#include "SpriteType.h"
#include "InputBuffer.h"

namespace RB
{
	class InputBufferRenderer : public GroupComponent
	{
	private:
		UIElement upleft;
		UIElement upright;
		UIElement downleft;
		UIElement downright;

		UIElement left;
		UIElement right;
		UIElement down;
		UIElement up;

		UIElement punch;

		olc::Decal* GetBufferDecal(InputType inputType)
		{
			switch (inputType)
			{
			case InputType::UP_RIGHT:
				return upright.ptrDecal;
			case InputType::DOWN_RIGHT:
				return downright.ptrDecal;
			case InputType::DOWN_LEFT:
				return downleft.ptrDecal;
			case InputType::UP_LEFT:
				return upleft.ptrDecal;

			case InputType::LEFT:
				return left.ptrDecal;
			case InputType::RIGHT:
				return right.ptrDecal;
			case InputType::DOWN:
				return down.ptrDecal;
			case InputType::UP:
				return up.ptrDecal;

			case InputType::WEAK_PUNCH:
				return punch.ptrDecal;
			}

			return nullptr;
		}
	public:
		InputBufferRenderer()
		{
			upleft.path = "PNG files/InputBuffer/upleft.png";
			upleft.spriteType = SpriteType::INPUT_BUFFER;
			upleft.SetHash();
			upleft.SetDecal();

			upright.path = "PNG files/InputBuffer/upright.png";
			upright.spriteType = SpriteType::INPUT_BUFFER;
			upright.SetHash();
			upright.SetDecal();

			downleft.path = "PNG files/InputBuffer/downleft.png";
			downleft.spriteType = SpriteType::INPUT_BUFFER;
			downleft.SetHash();
			downleft.SetDecal();

			downright.path = "PNG files/InputBuffer/downright.png";
			downright.spriteType = SpriteType::INPUT_BUFFER;
			downright.SetHash();
			downright.SetDecal();

			left.path = "PNG files/InputBuffer/left.png";
			left.spriteType = SpriteType::INPUT_BUFFER;
			left.SetHash();
			left.SetDecal();

			right.path = "PNG files/InputBuffer/right.png";
			right.spriteType = SpriteType::INPUT_BUFFER;
			right.SetHash();
			right.SetDecal();

			down.path = "PNG files/InputBuffer/down.png";
			down.spriteType = SpriteType::INPUT_BUFFER;
			down.SetHash();
			down.SetDecal();

			up.path = "PNG files/InputBuffer/up.png";
			up.spriteType = SpriteType::INPUT_BUFFER;
			up.SetHash();
			up.SetDecal();

			punch.path = "PNG files/InputBuffer/punch.png";
			punch.spriteType = SpriteType::INPUT_BUFFER;
			punch.SetHash();
			punch.SetDecal();

		}

		void RenderComponent() override
		{
			olc::vi2d startPos1(20, 100);
			RenderInputBuffer(startPos1, InputBuffer::ptr->vecP1Inputs);

			olc::vi2d startPos2(20, 150);
			RenderInputBuffer(startPos2, InputBuffer::ptr->vecP2Inputs);
		}

		void RenderInputBuffer(olc::vi2d& startPos, std::vector<InputElement>& vecInputs)
		{
			for (size_t i = 0; i < vecInputs.size(); i++)
			{
				olc::vf2d pos(0, 0);
				pos.x += ((20 * i) + (8 * i));
				pos += startPos;

				std::array<olc::vf2d, 4> points;

				points[0] = { 0, 0 };
				points[1] = { 0, 20 };
				points[2] = { 20, 20 };
				points[3] = { 20, 0 };

				points[0] += pos;
				points[1] += pos;
				points[2] += pos;
				points[3] += pos;

				olc::Decal* d = GetBufferDecal(vecInputs[i].inputType);

				if (d != nullptr)
				{
					if (vecInputs[i].inputType == InputType::WEAK_PUNCH)
					{
						olc::Renderer::ptrPGE->DrawWarpedDecal(d, points, olc::MAGENTA);
					}
					else
					{
						olc::Renderer::ptrPGE->DrawWarpedDecal(d, points, olc::RED);
					}
				}
			}
		}
	};
}