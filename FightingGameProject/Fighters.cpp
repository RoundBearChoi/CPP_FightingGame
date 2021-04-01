#include "Fighters.h"

namespace RB
{
	Fighters::Fighters()
	{
		upback.path = "PNG files/BoxColliderEditor/upback.png";
		upback.SetHash();
		upback.SetDecal();

		upforward.path = "PNG files/BoxColliderEditor/upforward.png";
		upforward.SetHash();
		upforward.SetDecal();

		downback.path = "PNG files/BoxColliderEditor/downback.png";
		downback.SetHash();
		downback.SetDecal();

		downforward.path = "PNG files/BoxColliderEditor/downforward.png";
		downforward.SetHash();
		downforward.SetDecal();
	}

	void Fighters::UpdateState(GameData& gameData)
	{
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

		//input queues
		InputQueue::ptr->AddInputs(gameData, arrObjs[0].objData, arrObjs[1].objData);

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
}