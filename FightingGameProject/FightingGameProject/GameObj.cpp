#include "GameObj.h"
#include "DevSettings.h"
#include "Renderer.h"

namespace RB
{
	GameObj::GameObj()
	{
		IF_COUT{ std::cout << "construcing GameObj: " << objData.GetCreationID() << std::endl; }
	}

	GameObj::~GameObj()
	{
		IF_COUT{ std::cout << "destructing GameObj: " << objData.GetCreationID() << std::endl; }
	}

	void GameObj::RenderPosition(Camera& cam)
	{
		olc::vi2d relative = RelativeVector::GetPosition(objData.GetPosition(), cam);

		RENDERER->FillCircle(relative, 2, olc::RED);
	}

	void GameObj::RenderSpriteSize(Camera& cam)
	{
		if (objData.GetOffsetType() == OffsetType::BOTTOM_CENTER)
		{
			int32_t halfWidth = objData.GetSpriteSize().x / 2;
			int32_t height = objData.GetSpriteSize().y;

			if (halfWidth > 0 && height > 0)
			{
				olc::vi2d leftTop = { objData.GetPosition().x - halfWidth, objData.GetPosition().y - height };
				olc::vi2d relativePos = RelativeVector::GetPosition(leftTop, cam);
				olc::vi2d relativeSize = RelativeVector::GetScale(objData.GetSpriteSize(), cam.GetZoom());

				RENDERER->DrawRect(relativePos.x, relativePos.y, relativeSize.x, relativeSize.y);
			}
		}
		else if (objData.GetOffsetType() == OffsetType::CENTER_CENTER)
		{
			int32_t halfWidth = objData.GetSpriteSize().x / 2;
			int32_t halfHeight = objData.GetSpriteSize().y / 2;

			if (halfWidth > 0 && halfHeight > 0)
			{
				olc::vi2d leftTop = { objData.GetPosition().x - halfWidth, objData.GetPosition().y - halfHeight };
				olc::vi2d relativePos = RelativeVector::GetPosition(leftTop, cam);
				olc::vi2d relativeSize = RelativeVector::GetScale(objData.GetSpriteSize(), cam.GetZoom());

				RENDERER->DrawRect(relativePos.x, relativePos.y, relativeSize.x, relativeSize.y);
			}
		}
	}
}