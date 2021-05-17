#include "FightersGroup.h"

namespace RB
{
	FightersGroup::FightersGroup(Camera* camera)
	{
		_camera = camera;
		_preloadFighter0 = new Preload_Fighter_0();

		_fighterDirection = new FighterDirection(&vecObjs);
		_fighterJump = new FighterJump(&vecObjs);
		_groundToGroundCollision = new FighterGroundToGroundCollision(&vecObjs);
		_specialMoveProcessor = new SpecialMoveProcessor(&vecObjs);
		_animationRenderer = new AnimationRenderer(&vecObjs, _camera);
		_inputBufferRenderer = new InputBufferRenderer();

		colliderData = new ColliderData(&vecObjs);
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

		delete _fighterDirection;
		delete _fighterJump;
		delete _groundToGroundCollision;
		delete _specialMoveProcessor;
		delete _animationRenderer;
		delete _inputBufferRenderer;

		delete _preloadFighter0;

		delete colliderData;
	}

	void FightersGroup::UpdateStates()
	{
		InputBuffer::ptr->AddInputs();

		_fighterDirection->Update();
		_groundToGroundCollision->Update();

		for (GameObj* obj : vecObjs)
		{
			obj->stateController->MakeStateTransition();

			if (obj->stateController->currentState != nullptr)
			{
				obj->stateController->currentState->RunUpdateProcess();
			}
		}

		_specialMoveProcessor->Update();
		_fighterJump->Update();
	}

	void FightersGroup::RenderStates(bool update)
	{
		_animationRenderer->Update();

		for (size_t i = 0; i < vecObjs.size(); i++)
		{
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
					vecObjs[i]->stateController->currentState->animationController.NextTileIndex();
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
				if (vecObjs[_index]->stateController->currentState != nullptr)
				{
					vecObjs[_index]->stateController->currentState->nextState = ptrState;
					return true;
				}
			}

			delete ptrState;
		}

		return false;
	}

	void FightersGroup::RenderObjPosition()
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			GameObj& obj = *vecObjs[i];

			obj.RenderPosition(*_camera);
			obj.objData.objBoxCollider.Render(*_camera, obj.objData.GetPosition(), olc::GREEN);

			if (obj.stateController->currentState != nullptr)
			{
				CheckCollisionMessage* check = obj.stateController->currentState->GetCollisionStatus();

				if (check)
				{
					for (size_t c = 0; c < check->vecBodies.size(); c++)
					{
						obj.RenderCollisionTiming(check->vecBodies[c], *_camera);
					}
				}
			}
		}

		_inputBufferRenderer->Update();
	}

	void FightersGroup::RenderBoxColliders()
	{
		for (int32_t i = 0; i < vecObjs.size(); i++)
		{
			vecObjs[i]->stateController->currentState->RenderColliderQuads(*_camera);
		}
	}

	std::array<olc::vi2d, 4> FightersGroup::GetBodyWorldQuad(int32_t fighterIndex, BodyType bodyType)
	{
		if (fighterIndex < vecObjs.size())
		{
			State* state = vecObjs[fighterIndex]->stateController->currentState;

			if (state != nullptr)
			{
				return state->GetColliderQuadsWorldPos(bodyType);
			}
		}

		std::array<olc::vi2d, 4> arr;
		return arr;
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

	void FightersGroup::SetFighterInfo(olc::vi2d _startingPos, PlayerType _playerType)
	{
		vecObjs.push_back(new GameObj());
		vecObjs.back()->objData.SetCreationID(vecObjs.size());
		vecObjs.back()->objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		vecObjs.back()->objData.SetPosition(_startingPos);
		vecObjs.back()->objData.SetPlayerType(_playerType);
	}

	GameObj* FightersGroup::GetEnemyObj(State& me)
	{
		for (GameObj* obj : vecObjs)
		{
			//compare addresses
			if (&(*obj->stateController->currentState) != &me)
			{
				return obj;
			}
		}

		return nullptr;
	}

	ObjData* FightersGroup::GetObjData(int32_t index)
	{
		if (index >= vecObjs.size())
		{
			return nullptr;
		}
		else
		{
			return &vecObjs[index]->objData;
		}
	}
}