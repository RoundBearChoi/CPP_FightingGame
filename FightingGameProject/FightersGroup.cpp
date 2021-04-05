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

		//check combos
		Hadouken h;
		h.SetCombo();

		for (size_t i = 0; i < InputBuffer::ptr->vecP1Inputs.size(); i++)
		{
			h.Check(InputBuffer::ptr->vecP1Inputs[i], i, arrObjs[0].objData);
		}

		//mark as processed
		if (h.Yes() == true)
		{
			for (size_t i = 0; i < h.correctBuffers.size(); i++)
			{
				size_t correctIndex = h.correctBuffers[i];

				if (correctIndex < InputBuffer::ptr->vecP1Inputs.size())
				{
					InputBuffer::ptr->vecP1Inputs[correctIndex].processed = true;
				}

				//make transition
				arrObjs[0].stateController.currentState->nextState = State::NewState<Fighter_0_Hadouken_Fire>();
			}
		}

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
			State* state = obj.stateController.currentState;

			if (state != nullptr)
			{
				state->RunUpdateProcess(obj.objData, gameData);

				//collision check between bodyparts
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
								//make transition
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

	void FightersGroup::RenderObjPosition(Camera& cam)
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

	void FightersGroup::RenderInputBuffer()
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
}