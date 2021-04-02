#include "Fighters.h"

namespace RB
{
	Fighters::Fighters()
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

	void Fighters::UpdateState(GameData& gameData)
	{
		//input queues
		InputBuffer::ptr->AddInputs(gameData);

		//forward directions
		if (arrObjs[0].objData.GetPosition().x < arrObjs[1].objData.GetPosition().x)
		{
			arrObjs[0].objData.SetLeftSide(true);
		}
		else if (arrObjs[0].objData.GetPosition().x > arrObjs[1].objData.GetPosition().x)
		{
			arrObjs[0].objData.SetLeftSide(false);
		}

		if (arrObjs[1].objData.GetPosition().x < arrObjs[0].objData.GetPosition().x)
		{
			arrObjs[1].objData.SetLeftSide(true);
		}
		else if (arrObjs[1].objData.GetPosition().x > arrObjs[0].objData.GetPosition().x)
		{
			arrObjs[1].objData.SetLeftSide(false);
		}

		for (GameObj& obj : arrObjs)
		{
			//forward directions
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
			State* state = obj.stateController.currentState;

			if (state != nullptr)
			{
				if (state->IsNew())
				{
					state->OnEnter(obj.objData, gameData);
				}

				state->UpdateState(obj.objData, gameData);
				state->updateCount++;

				if (obj.stateController.currentState->animationController.status.nDelayCount == 0)
				{
					state->OnAnimationUpdate(obj.objData, gameData);
				}

				//collision check
				CollisionStatus* col = state->GetCollisionStatus();

				if (col)
				{
					if (!col->processed)
					{
						col->processed = true;

						for (BodyType& b : col->vecBodies)
						{
							GameObj& enemy = *GetEnemyObj(*state);

							//temp - only checking against head
							BodyType enemyBody = BodyType::HEAD;

							if (DiagonalOverlap::IsColliding(obj, b, enemy, enemyBody))
							{
								enemy.stateController.currentState->nextState = State::NewState<Fighter_0_HitReaction_0>();
								IF_COUT{ std::cout << "overlap!" << std::endl; };
								IF_COUT{ std::cout << "attacker body index: " << (int32_t)b << std::endl; }
							}
						}

						IF_COUT{ std::cout << "collision check processed" << std::endl; };
					}
				}
			}
		}
	}

	void Fighters::RenderObjPosition(Camera& cam)
	{
		for (size_t i = 0; i < arrObjs.size(); i++)
		{
			GameObj& obj = arrObjs[i];

			//arrObjs[i].RenderSpriteSize(cam);
			obj.RenderPosition(cam);

			if (obj.stateController.currentState != nullptr)
			{
				CollisionStatus* check = obj.stateController.currentState->GetCollisionStatus();

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

	void Fighters::RenderStates(Camera& cam, bool update)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			SheetRenderer::Render(&arrObjs[i], cam);

			if (update)
			{
				arrObjs[i].stateController.currentState->animationController.NextTileIndex();
			}
		}
	}

	void Fighters::RenderBoxColliders(Camera& cam)
	{
		for (int32_t i = 0; i < arrObjs.size(); i++)
		{
			arrObjs[i].stateController.currentState->RenderColliderQuads(arrObjs[i].objData, cam);
		}
	}

	void Fighters::RenderInputBuffer()
	{
		olc::vi2d startPos = { 20, 100 };

		for (size_t i = 0; i < InputBuffer::ptr->vecP1Inputs.size(); i++)
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

			olc::Decal* d = GetBufferDecal(InputBuffer::ptr->vecP1Inputs[i].inputType);

			if (d != nullptr)
			{
				if (InputBuffer::ptr->vecP1Inputs[i].inputType == InputType::WEAK_PUNCH)
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

	void Fighters::SetFighterInfo(int32_t _index, olc::vi2d _startingPos, PlayerType _playerType)
	{
		size_t count = CreationCount::UpdateCount();

		arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		arrObjs[_index].objData.SetPosition(_startingPos);

		arrObjs[_index].objData.SetCreationID(count);
		arrObjs[_index].stateController.SetCreationID(count);

		arrObjs[_index].objData.SetPlayerType(_playerType);
	}

	State* Fighters::GetEnemyState(State& me)
	{
		for (GameObj& obj : arrObjs)
		{
			//compare addresses
			if (&(*obj.stateController.currentState) != &me)
			{
				return obj.stateController.currentState;
			}
		}

		return nullptr;
	}

	GameObj* Fighters::GetEnemyObj(State& me)
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

	olc::Decal* Fighters::GetBufferDecal(InputType inputType)
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
}