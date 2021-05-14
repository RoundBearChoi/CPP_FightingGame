#include "GameObj.h"

namespace RB
{
	GameObj::GameObj(StateFactory* stateFactory)
	{
		IF_COUT{ std::cout << "constructing GameObj: " << objData.GetCreationID() << std::endl; };

		_stateFactory = stateFactory;
		
		stateController = new StateController(_stateFactory);
	}

	GameObj::~GameObj()
	{
		IF_COUT{ std::cout << "destructing GameObj: " << objData.GetCreationID() << std::endl; };

		delete stateController;
	}

	void GameObj::RenderPosition(Camera& cam)
	{
		olc::vi2d relative = ScreenVector::GetScreenPosition(objData.GetPosition(), cam);

		if (DevSettings::renderMode == RenderMode::DEBUG_ONLY || DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG)
		{
			olc::Renderer::ptrPGE->FillCircle(relative, 2, olc::RED);
		}
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
				olc::vi2d relativePos = ScreenVector::GetScreenPosition(leftTop, cam);
				olc::vi2d relativeSize = ScreenVector::GetScale(objData.GetSpriteSize(), cam.GetZoom());

				olc::Renderer::ptrPGE->DrawRect(relativePos.x, relativePos.y, relativeSize.x, relativeSize.y);
			}
		}
		else if (objData.GetOffsetType() == OffsetType::CENTER_CENTER)
		{
			int32_t halfWidth = objData.GetSpriteSize().x / 2;
			int32_t halfHeight = objData.GetSpriteSize().y / 2;

			if (halfWidth > 0 && halfHeight > 0)
			{
				olc::vi2d leftTop = { objData.GetPosition().x - halfWidth, objData.GetPosition().y - halfHeight };
				olc::vi2d relativePos = ScreenVector::GetScreenPosition(leftTop, cam);
				olc::vi2d relativeSize = ScreenVector::GetScale(objData.GetSpriteSize(), cam.GetZoom());

				olc::Renderer::ptrPGE->DrawRect(relativePos.x, relativePos.y, relativeSize.x, relativeSize.y);
			}
		}
	}

	void GameObj::RenderCollisionTiming(BodyType _bodyType, Camera& cam)
	{
		if (DevSettings::renderMode == RenderMode::DEBUG_ONLY || DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG)
		{
			//draw center position
			olc::vi2d playerPos = ScreenVector::GetScreenPosition(objData.GetPosition(), cam);
			olc::vi2d colliderPos = stateController->currentState->GetColliderWorldPos(_bodyType, objData);

			olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(colliderPos, cam), olc::RED);

			//draw quads
			std::array<olc::vi2d, 4> quads = stateController->currentState->GetColliderQuadsWorldPos(_bodyType, objData);

			if (DevSettings::renderMode == RenderMode::DEBUG_ONLY || DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG)
			{
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[0], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[1], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[2], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[3], cam), olc::YELLOW);
			}
		}
	}
}