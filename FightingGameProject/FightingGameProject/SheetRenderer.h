#pragma once
#include "olcPixelGameEngine.h"
#include "DecalLoader.h"
#include "GameObj.h"
#include "AnimationStatus.h"

namespace RB
{
	class SheetRenderer
	{
	private:
		static void RenderOnOffset(olc::PixelGameEngine* ptrEngine, DecalLoader* decalLoader, GameObj* obj, AnimationStatus* status, const olc::vi2d& camPos, const float& zoomScale)
		{
			int32_t x = obj->objData.GetPosition().x;
			int32_t y = obj->objData.GetPosition().y;
			int32_t width = obj->objData.GetSpriteSize().x;
			int32_t height = obj->objData.GetSpriteSize().y;

			std::array<olc::vf2d, 4> points;

			if (obj->objData.GetOffsetType() == OffsetType::BOTTOM_CENTER)
			{
				if (!status->bReverseDecal)
				{
					points[0] = { (float)x - (float)width / 2.0f, (float)y - (float)height };
					points[1] = { (float)x - (float)width / 2.0f, (float)y };
					points[2] = { (float)x + (float)width / 2.0f, (float)y };
					points[3] = { (float)x + (float)width / 2.0f, (float)y - (float)height };
				}
				else
				{
					points[0] = { (float)x + (float)width / 2.0f, (float)y - (float)height };
					points[1] = { (float)x + (float)width / 2.0f, (float)y };
					points[2] = { (float)x - (float)width / 2.0f, (float)y };
					points[3] = { (float)x - (float)width / 2.0f, (float)y - (float)height };
				}
			}
			else if (obj->objData.GetOffsetType() == OffsetType::CENTER_CENTER)
			{
				if (!status->bReverseDecal)
				{
					points[0] = { (float)x - (float)width / 2.0f, (float)y - (float)height / 2.0f };
					points[1] = { (float)x - (float)width / 2.0f, (float)y + (float)height / 2.0f };
					points[2] = { (float)x + (float)width / 2.0f, (float)y + (float)height / 2.0f };
					points[3] = { (float)x + (float)width / 2.0f, (float)y - (float)height / 2.0f };
				}
				else
				{
					points[0] = { (float)x + (float)width / 2.0f, (float)y - (float)height / 2.0f };
					points[1] = { (float)x + (float)width / 2.0f, (float)y + (float)height / 2.0f };
					points[2] = { (float)x - (float)width / 2.0f, (float)y + (float)height / 2.0f };
					points[3] = { (float)x - (float)width / 2.0f, (float)y - (float)height / 2.0f };
				}
			}

			olc::Decal* d = decalLoader->GetDecal(status->decalTypeIndex);

			std::array<olc::vf2d, 4> relativePoints;
			relativePoints[0] = RelativeVector::Get(points[0], camPos, zoomScale);
			relativePoints[1] = RelativeVector::Get(points[1], camPos, zoomScale);
			relativePoints[2] = RelativeVector::Get(points[2], camPos, zoomScale);
			relativePoints[3] = RelativeVector::Get(points[3], camPos, zoomScale);

			ptrEngine->DrawPartialWarpedDecal(d, relativePoints, status->sourcePos, status->sourceSize);
		}

	public:
		static void Render(olc::PixelGameEngine* ptrEngine, DecalLoader* decalLoader, GameObj* obj, const olc::vi2d& camPos, const float& zoomScale, bool update)
		{
			AnimationStatus* status = obj->stateController.currentState->animationController.GetRenderData(update);

			if (status->sourceSize.x > 0.0f && status->sourceSize.y > 0.0f)
			{
				RenderOnOffset(ptrEngine, decalLoader, obj, status, camPos, zoomScale);
			}
		}
	};
}