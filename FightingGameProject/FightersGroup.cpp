#include "FightersGroup.h"

namespace RB
{
	FightersGroup::FightersGroup()
	{


		ptrFighterDirection = new FighterDirection;
		ptrFighterJump = new FighterJump;
		ptrGroundToGroundCollision = new FighterGroundToGroundCollision;
		ptrSpecialMoveProcessor = new SpecialMoveProcessor;
		ptrAnimationRenderer = new AnimationRenderer;
		ptrInputBufferRenderer = new InputBufferRenderer;
	}

	FightersGroup::~FightersGroup()
	{
		if (vecObjs.size() != 0)
		{
			IF_COUT{ std::cout << std::endl; };

			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				IF_COUT{ std::cout << "destructing fighter: " << i << std::endl; };
				delete vecObjs[i];
			}

			IF_COUT{ std::cout << std::endl; };
		}

		delete ptrFighterDirection;
		delete ptrFighterJump;
		delete ptrGroundToGroundCollision;
		delete ptrSpecialMoveProcessor;
		delete ptrAnimationRenderer;
		delete ptrInputBufferRenderer;
	}

	void FightersGroup::UpdateStates(GameData& gameData)
	{
		InputBuffer::ptr->AddInputs(gameData);

		ptrFighterDirection->Update(vecObjs);
		ptrGroundToGroundCollision->Update(vecObjs);

		for (GameObj* obj : vecObjs)
		{
			obj->stateController.MakeStateTransition();

			if (obj->stateController.currentState != nullptr)
			{
				obj->stateController.currentState->RunUpdateProcess(obj->objData, gameData);
			}

			ptrSpecialMoveProcessor->Update(*obj);
			ptrFighterJump->Update(*obj, gameData);
		}
	}

	void FightersGroup::RenderObjPosition(Camera& cam)
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			GameObj& obj = *vecObjs[i];

			obj.RenderPosition(cam);
			obj.objData.objBoxCollider.Render(cam, obj.objData.GetPosition(), olc::GREEN);

			if (obj.stateController.currentState != nullptr)
			{
				CheckCollisionMessage* check = obj.stateController.currentState->GetCollisionStatus();

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
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			ptrAnimationRenderer->Update(*vecObjs[i], cam);

			if (update)
			{
				bool slowmotion = false;

				for (size_t i = 0; i < vecSlowMotion.size(); i++)
				{
					if (vecSlowMotion[i].SkipUpdate())
					{
						slowmotion = true;
						break;
					}
				}

				if (!slowmotion)
				{
					vecObjs[i]->stateController.currentState->animationController.NextTileIndex();
				}
			}
		}
	}

	bool FightersGroup::SetNextState(int32_t _index, State* ptrState)
	{
		if (ptrState != nullptr)
		{
			if (_index < vecObjs.size())
			{
				if (vecObjs[_index]->stateController.currentState != nullptr)
				{
					vecObjs[_index]->stateController.currentState->nextState = ptrState;
					return true;
				}
			}

			delete ptrState;
		}

		return false;
	}

	void FightersGroup::RenderBoxColliders(Camera& cam)
	{
		for (int32_t i = 0; i < vecObjs.size(); i++)
		{
			vecObjs[i]->stateController.currentState->RenderColliderQuads(vecObjs[i]->objData, cam);
		}
	}

	std::array<olc::vi2d, 4> FightersGroup::GetObjBoxColliderWorldQuad(size_t index)
	{
		std::array<olc::vi2d, 4> arr;
		return arr;
	}

	olc::vi2d FightersGroup::GetBodyWorldPos(int32_t fighterIndex, BodyType bodyType)
	{
		if (fighterIndex < vecObjs.size())
		{
			State* state = vecObjs[fighterIndex]->stateController.currentState;

			if (state != nullptr)
			{
				return state->GetColliderWorldPos(bodyType, vecObjs[fighterIndex]->objData);
			}
		}

		return { 0, 0 };
	}

	std::array<olc::vi2d, 4> FightersGroup::GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType)
	{
		if (fighterIndex < vecObjs.size())
		{
			State* state = vecObjs[fighterIndex]->stateController.currentState;

			if (state != nullptr)
			{
				return state->GetColliderQuadsWorldPos(bodyType, vecObjs[fighterIndex]->objData);
			}
		}

		std::array<olc::vi2d, 4> arr;
		return arr;
	}

	void FightersGroup::RenderComponents()
	{
		ptrInputBufferRenderer->Update();
	}

	void FightersGroup::SetFighterInfo(olc::vi2d _startingPos, PlayerType _playerType)
	{
		vecObjs.push_back(new GameObj);
		vecObjs.back()->objData.SetCreationID(vecObjs.size());
		vecObjs.back()->objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		vecObjs.back()->objData.SetPosition(_startingPos);
		vecObjs.back()->objData.SetPlayerType(_playerType);
	}

	void FightersGroup::AddJumpProcessor(int32_t index, int32_t upForce, int32_t sideForce)
	{
		vecObjs[index]->objData.CreateJumpProcessor();
		vecObjs[index]->objData.ptrJumpProcessor->allowControl = false;
		vecObjs[index]->objData.ptrJumpProcessor->moveBack = true;
		vecObjs[index]->objData.ptrJumpProcessor->moveHorizontally = true;
		vecObjs[index]->objData.ptrJumpProcessor->minimumSideForce = 1;

		vecObjs[index]->objData.ptrJumpProcessor->SetUpForce(upForce);
		vecObjs[index]->objData.ptrJumpProcessor->SetSideForce(sideForce);
	}

	GameObj* FightersGroup::GetEnemyObj(State& me)
	{
		for (GameObj* obj : vecObjs)
		{
			//compare addresses
			if (&(*obj->stateController.currentState) != &me)
			{
				return obj;
			}
		}

		return nullptr;
	}

	std::vector<CreateProjectileMessage>* FightersGroup::GetProjectileQueues(size_t _index)
	{
		if (_index < vecObjs.size())
		{
			return &vecObjs[_index]->stateController.currentState->vecCreateProjectiles;
		}

		return nullptr;
	}
}