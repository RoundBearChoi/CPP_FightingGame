#include "GameObj.h"

namespace RB
{
	GameObj::GameObj()
	{
		IF_COUT{ std::cout << "constructing GameObj: " << objData.GetCreationID() << std::endl; };

		stateController = new StateController();
	}

	GameObj::~GameObj()
	{
		IF_COUT{ std::cout << "destructing GameObj: " << objData.GetCreationID() << std::endl; };

		delete stateController;
	}

	bool GameObj::SetNextState(State* ptrState)
	{
		if (ptrState != nullptr)
		{
			if (stateController->currentState != nullptr)
			{
				stateController->currentState->nextState = ptrState;
				return true;
			}

			delete ptrState;
			return false;
		}
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
			olc::vi2d colliderPos = stateController->currentState->GetColliderWorldPos(_bodyType);

			olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(colliderPos, cam), olc::RED);

			//draw quads
			std::array<olc::vi2d, 4> quads = stateController->currentState->GetColliderQuadsWorldPos(_bodyType);

			if (DevSettings::renderMode == RenderMode::DEBUG_ONLY || DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG)
			{
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[0], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[1], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[2], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[3], cam), olc::YELLOW);
			}
		}
	}

	void GameObj::AddJump(int32_t upForce, int32_t sideForce)
	{
		objData.CreateJumpProcessor();
		objData.ptrJumpProcessor->allowControl = false;
		objData.ptrJumpProcessor->moveBack = true;
		objData.ptrJumpProcessor->moveHorizontally = true;
		objData.ptrJumpProcessor->minimumSideForce = 1;

		objData.ptrJumpProcessor->SetUpForce(upForce);
		objData.ptrJumpProcessor->SetSideForce(sideForce);
	}

	olc::vi2d GameObj::GetBodyWorldPos(BodyType bodyType)
	{
		State* state = stateController->currentState;

		if (state != nullptr)
		{
			return state->GetColliderWorldPos(bodyType);
		}

		return { 0, 0 };
	}

	std::array<olc::vi2d, 4> GameObj::GetBodyWorldQuad(BodyType bodyType)
	{
		State* state = stateController->currentState;

		if (state != nullptr)
		{
			return state->GetColliderQuadsWorldPos(bodyType);
		}

		std::array<olc::vi2d, 4> arr;
		return arr;
	}

	olc::vi2d GameObj::GetBoxColliderWorldPos()
	{
		olc::vi2d relativePos = objData.objBoxCollider.RelativePosition();
		olc::vi2d worldPos = relativePos + objData.GetPosition();

		return worldPos;
	}
}