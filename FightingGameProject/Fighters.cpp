#include "Fighters.h"

namespace RB
{
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
			State* s = obj.stateController.currentState;

			if (s != nullptr)
			{
				if (s->IsNew())
				{
					s->OnEnter(obj.objData, gameData);
				}

				s->UpdateState(obj.objData, gameData);

				if (obj.stateController.currentState->animationController.status.nDelayCount == 0)
				{
					s->OnAnimationUpdate(obj.objData, gameData);
				}

				//collision check
				CollisionCheck* collisionCheck = s->GetCollisionCheck();

				if (collisionCheck)
				{
					if (!collisionCheck->processed)
					{
						collisionCheck->processed = true;

						for (BodyType& b : collisionCheck->vecBodies)
						{
							GameObj& enemy = *GetEnemyObj(*s);

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
				CollisionCheck* check = obj.stateController.currentState->GetCollisionCheck();

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