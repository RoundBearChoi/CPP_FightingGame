#include "GameObj.h"

namespace RB
{
	class Fighter_0_HitReaction_Up;
	class Fighter_0_HitReaction_Side;

	GameObj::GameObj()
	{
		IF_COUT{ std::cout << "constructing GameObj: " << objData.GetCreationID() << std::endl; };

		_stateController = new StateController();

		collisionStay = new CollisionStay(&objData);
	}

	GameObj::~GameObj()
	{
		IF_COUT{ std::cout << "destructing GameObj: " << objData.GetCreationID() << std::endl; };

		delete _stateController;
		delete collisionStay;
	}

	State* GameObj::GetCurrentState()
	{
		return _stateController->currentState;
	}

	void GameObj::SetCurrentState(State* state)
	{
		_stateController->currentState = state;
	}

	bool GameObj::SetNextState(State* ptrState)
	{
		if (ptrState != nullptr)
		{
			if (_stateController->currentState != nullptr)
			{
				_stateController->currentState->nextState = ptrState;
				return true;
			}

			delete ptrState;
		}
		
		return false;
	}

	StateController* GameObj::GetStateController()
	{
		return _stateController;
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
			olc::vi2d colliderPos = _stateController->currentState->GetColliderWorldPos(_bodyType);

			olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(colliderPos, cam), olc::RED);

			//draw quads
			std::array<olc::vi2d, 4> quads = _stateController->currentState->GetColliderQuadsWorldPos(_bodyType);

			if (DevSettings::renderMode == RenderMode::DEBUG_ONLY || DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG)
			{
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[0], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[1], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[2], cam), olc::YELLOW);
				olc::Renderer::ptrPGE->DrawLine(playerPos, ScreenVector::GetScreenPosition(quads[3], cam), olc::YELLOW);
			}
		}
	}

	olc::vi2d GameObj::GetBodyWorldPos(BodyType bodyType)
	{
		State* state = _stateController->currentState;

		if (state != nullptr)
		{
			return state->GetColliderWorldPos(bodyType);
		}

		return { 0, 0 };
	}

	std::array<olc::vi2d, 4> GameObj::GetBodyWorldQuad(BodyType bodyType)
	{
		State* state = _stateController->currentState;

		if (state != nullptr)
		{
			return state->GetColliderQuadsWorldPos(bodyType);
		}

		std::array<olc::vi2d, 4> arr;
		return arr;
	}

	olc::vi2d GameObj::GetBoxColliderWorldPos()
	{
		olc::vi2d relativePos = collisionData.objBoxCollider.RelativePosition();
		olc::vi2d worldPos = relativePos + objData.GetPosition();

		return worldPos;
	}

	std::array<olc::vi2d, 4> GameObj::GetBoxColliderWorldQuad()
	{
		std::array<olc::vi2d, 4> arr;

		arr[0] = collisionData.objBoxCollider.RelativePoint0();
		arr[1] = collisionData.objBoxCollider.RelativePoint1();
		arr[2] = collisionData.objBoxCollider.RelativePoint2();
		arr[3] = collisionData.objBoxCollider.RelativePoint3();

		olc::vi2d relativePos = collisionData.objBoxCollider.RelativePosition();

		arr[0] += relativePos;
		arr[1] += relativePos;
		arr[2] += relativePos;
		arr[3] += relativePos;

		olc::vi2d playerPos = objData.GetPosition();

		arr[0] += playerPos;
		arr[1] += playerPos;
		arr[2] += playerPos;
		arr[3] += playerPos;

		return arr;
	}
}