#include "FightersGroup.h"

namespace RB
{
	FightersGroup::FightersGroup()
	{
		//initialize components
		ptrAnimationRenderer = new AnimationRenderer;
		ptrInputBufferRenderer = new InputBufferRenderer;
	}

	FightersGroup::~FightersGroup()
	{
		delete ptrAnimationRenderer;
		delete ptrInputBufferRenderer;
	}

	void FightersGroup::UpdateStates(GameData& gameData)
	{
		//input queues
		InputBuffer::ptr->AddInputs(gameData);

		//directions
		arrObjs[0].objData.UpdateFigherDirection(arrObjs[1].objData);
		arrObjs[1].objData.UpdateFigherDirection(arrObjs[0].objData);

		//special moves
		specialMoveProcessor.Update(arrObjs);

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

			fighterJump.Update(obj, gameData);
		}

		fighterGroundToGroundCollision.Update(arrObjs);
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
			ptrAnimationRenderer->RenderComponent(&arrObjs[i], cam);

			if (update)
			{
				arrObjs[i].stateController.currentState->animationController.NextTileIndex();
			}
		}
	}

	bool FightersGroup::SetNextState(int32_t _index, State* ptrState)
	{
		if (ptrState != nullptr)
		{
			if (_index < arrObjs.size())
			{
				if (arrObjs[_index].stateController.currentState != nullptr)
				{
					arrObjs[_index].stateController.currentState->nextState = ptrState;
					return true;
				}
			}

			delete ptrState;
		}

		return false;
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

	void FightersGroup::RenderComponents()
	{
		ptrInputBufferRenderer->RenderComponent();
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

	void FightersGroup::SetFighterInfo(int32_t _index, olc::vi2d _startingPos, PlayerType _playerType)
	{
		size_t count = CreationCount::UpdateCount();

		arrObjs[_index].objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		arrObjs[_index].objData.SetPosition(_startingPos);
		arrObjs[_index].objData.SetCreationID(count);
		arrObjs[_index].objData.SetPlayerType(_playerType);
	}

	void FightersGroup::AddJumpProcessor(int32_t index, int32_t upForce, int32_t sideForce)
	{
		arrObjs[index].objData.CreateJumpProcessor();
		arrObjs[index].objData.ptrJumpProcessor->allowControl = false;
		arrObjs[index].objData.ptrJumpProcessor->moveBack = true;
		arrObjs[index].objData.ptrJumpProcessor->moveHorizontally = true;
		arrObjs[index].objData.ptrJumpProcessor->minimumSideForce = 1;

		arrObjs[index].objData.ptrJumpProcessor->SetUpForce(upForce);
		arrObjs[index].objData.ptrJumpProcessor->SetSideForce(sideForce);
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

	std::vector<CreateProjectile>* FightersGroup::GetProjectileQueues(size_t _index)
	{
		if (_index < arrObjs.size())
		{
			return &arrObjs[_index].stateController.currentState->vecCreateProjectiles;
		}

		return nullptr;
	}

	int32_t FightersGroup::GetCollisionCount(int32_t fighterIndex)
	{
		if (fighterIndex < arrObjs.size())
		{
			if (arrObjs[fighterIndex].stateController.currentState != nullptr)
			{
				return arrObjs[fighterIndex].stateController.currentState->bodyCollisionCount;
			}
		}

		return 0;
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

	void FightersGroup::AddCollisionCount(int32_t fighterIndex)
	{
		arrObjs[fighterIndex].stateController.currentState->bodyCollisionCount++;
	}
}