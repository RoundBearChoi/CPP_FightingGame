#include "FightersGroup.h"

namespace RB
{
	FightersGroup::FightersGroup()
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

		punch.path = "PNG files/InputBuffer/punch.png";
		punch.spriteType = SpriteType::INPUT_BUFFER;
		punch.SetHash();
		punch.SetDecal();
	}

	void FightersGroup::UpdateStates(GameData& gameData)
	{
		//input queues
		InputBuffer::ptr->AddInputs(gameData);

		//directions
		arrObjs[0].objData.UpdateFigherDirection(arrObjs[1].objData);
		arrObjs[1].objData.UpdateFigherDirection(arrObjs[0].objData);

		//check special move
		Hadouken h1;
		Hadouken h2;
		h1.SetCombo();
		h2.SetCombo();

		if (ComboChecker::TriggerSpecialMove(h1, InputBuffer::ptr->vecP1Inputs, arrObjs[0]))
		{
			arrObjs[0].stateController.currentState->nextState = State::NewState<Fighter_0_Hadouken_Fire>();
		}

		if (ComboChecker::TriggerSpecialMove(h2, InputBuffer::ptr->vecP2Inputs, arrObjs[1]))
		{
			arrObjs[1].stateController.currentState->nextState = State::NewState<Fighter_0_Hadouken_Fire>();
		}

		//position before update
		arrObjs[0].objData.lastPosition = arrObjs[0].objData.GetPosition();
		arrObjs[1].objData.lastPosition = arrObjs[1].objData.GetPosition();

		//main update
		for (GameObj& obj : arrObjs)
		{
			//change directions
			obj.stateController.MakeStateTransition();

			if (obj.objData.IsOnLeftSide())
			{
				obj.objData.FaceRight(true);
			}
			else
			{
				obj.objData.FaceRight(false);
			}

			//update state
			if (obj.stateController.currentState != nullptr)
			{
				obj.stateController.currentState->RunUpdateProcess(obj.objData, gameData);
			}
		}

		//resolve body mass collision

		//ground vs ground
		if (arrObjs[0].objData.GetPosition().y == 0 && arrObjs[1].objData.GetPosition().y == 0)
		{
			if (AABB::IsColliding(
				arrObjs[0].objData.objBoxCollider, arrObjs[0].objData.GetPosition(), //p1 obj boxcollider
				arrObjs[1].objData.objBoxCollider, arrObjs[1].objData.GetPosition())) //p2 obj boxcollider
			{
				olc::vi2d relMidPoint = arrObjs[1].objData.GetPosition() - arrObjs[0].objData.GetPosition();
				relMidPoint.x = (int32_t)std::round(relMidPoint.x / 2.0f);
				relMidPoint.y = (int32_t)std::round(relMidPoint.y / 2.0f);
				olc::vf2d midPoint = arrObjs[0].objData.GetPosition() + relMidPoint;

				olc::vi2d p1Dir = arrObjs[0].objData.GetPosition() - midPoint;
				olc::vi2d p2Dir = arrObjs[1].objData.GetPosition() - midPoint;

				olc::vf2d p1rel = (olc::vf2d)Normalize::Norm(p1Dir) * (float)arrObjs[0].objData.objBoxCollider.Width() / 2.0f;
				olc::vf2d p2rel = (olc::vf2d)Normalize::Norm(p2Dir) * (float)arrObjs[1].objData.objBoxCollider.Width() / 2.0f;

				olc::vf2d p1Resolved = midPoint + p1rel;
				olc::vf2d p2Resolved = midPoint + p2rel;

				olc::vi2d p1Rounded{ 0, 0 };
				olc::vi2d p2Rounded{ 0, 0 };

				p1Rounded.x = (int32_t)std::round(p1Resolved.x);
				p2Rounded.x = (int32_t)std::round(p2Resolved.x);

				arrObjs[0].objData.SetPosition(p1Rounded);
				arrObjs[1].objData.SetPosition(p2Rounded);
			}
		}
	}

	void FightersGroup::RenderObjPosition(Camera& cam)
	{
		for (size_t i = 0; i < arrObjs.size(); i++)
		{
			GameObj& obj = arrObjs[i];

			//arrObjs[i].RenderSpriteSize(cam);
			obj.RenderPosition(cam);
			obj.objData.objBoxCollider.Render(cam, obj.objData.GetPosition(), olc::GREEN);

			if (obj.stateController.currentState != nullptr)
			{
				CollisionQueue* check = obj.stateController.currentState->GetCollisionStatus();

				if (check)
				{
					for (size_t c = 0; c < check->vecBodies.size(); c++)
					{
						obj.RenderCollisionTiming(check->vecBodies[c], cam);
					}
				}
			}
		}
	}

	void FightersGroup::RenderStates(Camera& cam, bool update)
	{
		for (size_t i = 0; i < arrObjs.size(); i++)
		{
			SheetRenderer::Render(&arrObjs[i], cam);

			if (update)
			{
				arrObjs[i].stateController.currentState->animationController.NextTileIndex();
			}
		}
	}

	void FightersGroup::RenderBoxColliders(Camera& cam)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			arrObjs[i].stateController.currentState->RenderColliderQuads(arrObjs[i].objData, cam);
		}
	}

	size_t FightersGroup::GetObjCount()
	{
		return arrObjs.size();
	}

	size_t FightersGroup::GetObjCreationID(size_t index)
	{
		if (index < arrObjs.size())
		{
			return (arrObjs[index].objData.GetCreationID());
		}

		return 0;
	}

	olc::vi2d FightersGroup::GetObjWorldPos(size_t index)
	{
		if (index < arrObjs.size())
		{
			return arrObjs[index].objData.GetPosition();
		}
		
		return { 0, 0 };
	}

	olc::vi2d FightersGroup::GetObjBoxColliderWorldPos(size_t index)
	{
		return { 0, 0 };
	}

	std::array<olc::vi2d, 4> FightersGroup::GetObjBoxColliderWorldQuad(size_t index)
	{
		std::array<olc::vi2d, 4> arr;
		return arr;
	}

	CollisionQueue* FightersGroup::GetCollisionQueue(size_t index)
	{
		if (index < arrObjs.size())
		{
			if (arrObjs[index].stateController.currentState != nullptr)
			{
				if (arrObjs[index].stateController.currentState->vecCollisionStatus.size() > 0)
				{
					return arrObjs[index].stateController.currentState->GetCollisionStatus();
				}
			}
		}

		return nullptr;
	}

	void FightersGroup::RenderInputBuffer(olc::vi2d& startPos, std::vector<InputElement>& vecInputs)
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

	void FightersGroup::SetFighterInfo(int32_t _index, olc::vi2d _startingPos, PlayerType _playerType)
	{
		size_t count = CreationCount::UpdateCount();

		arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		arrObjs[_index].objData.SetPosition(_startingPos);
		arrObjs[_index].objData.SetCreationID(count);
		arrObjs[_index].objData.SetPlayerType(_playerType);
	}

	GameObj* FightersGroup::GetEnemyObj(State& me)
	{
		for (GameObj& obj : arrObjs)
		{
			//compare addresses
			if (&(*obj.stateController.currentState) != &me)
			{
				return &obj;
			}
		}

		return nullptr;
	}

	olc::Decal* FightersGroup::GetBufferDecal(InputType inputType)
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

		case InputType::WEAK_PUNCH:
			return punch.ptrDecal;
		}

		return nullptr;
	}

	std::vector<CreateProjectile>* FightersGroup::GetProjectileQueues(size_t _index)
	{
		if (_index < arrObjs.size())
		{
			return &arrObjs[_index].stateController.currentState->vecCreateProjectiles;
		}

		return nullptr;
	}

	olc::vi2d FightersGroup::GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType)
	{
		if (fighterIndex < arrObjs.size())
		{
			State* state = arrObjs[fighterIndex].stateController.currentState;

			if (state != nullptr)
			{
				return state->GetColliderWorldPos(bodyType, arrObjs[fighterIndex].objData);
			}
		}

		return { 0, 0 };
	}

	std::array<olc::vi2d, 4> FightersGroup::GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType)
	{
		if (fighterIndex < arrObjs.size())
		{
			State* state = arrObjs[fighterIndex].stateController.currentState;

			if (state != nullptr)
			{
				return state->GetColliderQuadsWorldPos(bodyType, arrObjs[fighterIndex].objData);
			}
		}

		std::array<olc::vi2d, 4> arr;
		return arr;
	}

	int32_t* FightersGroup::CollisionCount(int32_t fighterIndex)
	{
		if (fighterIndex < arrObjs.size())
		{
			if (arrObjs[fighterIndex].stateController.currentState != nullptr)
			{
				return &arrObjs[fighterIndex].stateController.currentState->bodyCollisionCount;
			}
		}

		return nullptr;
	}

	int32_t FightersGroup::MaxCollisions(int32_t fighterIndex)
	{
		if (fighterIndex < arrObjs.size())
		{
			if (arrObjs[fighterIndex].stateController.currentState != nullptr)
			{
				return arrObjs[fighterIndex].stateController.currentState->maxBodyCollisions;
			}
		}

		return 0;
	}
}