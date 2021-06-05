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

		//colliderData = new ColliderData(&vecObjs);
		collisionData = new CollisionData(&vecObjs);
		jumpAdder = new JumpAdder(&vecObjs);
		messageGetter = new MessageGetter(&vecObjs);
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

		//delete colliderData;
		delete collisionData;
		delete jumpAdder;
		delete messageGetter;
	}

	void FightersGroup::UpdateStates()
	{
		InputBuffer::ptr->AddInputs();

		_fighterDirection->Update();
		_groundToGroundCollision->Update();
		_specialMoveProcessor->Update();
		_fighterJump->Update();

		for (GameObj* obj : vecObjs)
		{
			obj->stateController->MakeStateTransition();

			if (obj->stateController->currentState != nullptr)
			{
				obj->stateController->currentState->RunUpdateProcess();
			}
		}
	}

	void FightersGroup::RenderStates()
	{
		_animationRenderer->Update();
	}

	void FightersGroup::UpdateSpriteTileIndex()
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			vecObjs[i]->stateController->currentState->animationController.NextTileIndex();
		}
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