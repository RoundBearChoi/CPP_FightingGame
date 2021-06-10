#include "FightersGroup.h"

namespace RB
{
	FightersGroup::FightersGroup(Camera* camera)
	{
		_camera = camera;
		_preloadFighter0 = new Preload_Fighter_0();

		_vecUpdateComponents.push_back(new FighterDirection(&_vecObjs));
		_vecUpdateComponents.push_back(new FighterJump(&_vecObjs));
		_vecUpdateComponents.push_back(new FighterGroundToGroundCollision(&_vecObjs));
		_vecUpdateComponents.push_back(new SpecialMoveProcessor(&_vecObjs));

		_vecRenderComponents.push_back(new AnimationRenderer(&_vecObjs, _camera));
		_vecRenderComponents.push_back(new PreviousPositionRenderer(&_vecObjs, _camera));

		_inputBufferRenderer = new InputBufferRenderer();

		_updater = new FightersFixedUpdater(this, &_vecUpdateComponents);

		FightersHitStopMessage::SetReceiver(_updater);
	}

	FightersGroup::~FightersGroup()
	{
		if (_vecObjs.size() != 0)
		{
			IF_COUT{ std::cout << std::endl; };

			for (size_t i = 0; i < _vecObjs.size(); i++)
			{
				IF_COUT{ std::cout << "destructing fighter: " << i << std::endl; };
				delete _vecObjs[i];
			}

			IF_COUT{ std::cout << std::endl; };
		}

		for (size_t i = 0; i < _vecUpdateComponents.size(); i++)
		{
			delete _vecUpdateComponents[i];
		}

		for (size_t i = 0; i < _vecRenderComponents.size(); i++)
		{
			delete _vecRenderComponents[i];
		}

		delete _inputBufferRenderer;
		delete _preloadFighter0;
		delete _updater;
	}

	void FightersGroup::UpdateStates()
	{
		_updater->CustomUpdate();
	}

	void FightersGroup::RenderStates()
	{
		for (size_t i = 0; i < _vecRenderComponents.size(); i++)
		{
			_vecRenderComponents[i]->Update();
		}
	}

	void FightersGroup::UpdateSpriteTileIndex()
	{
		for (size_t i = 0; i < _vecObjs.size(); i++)
		{
			if (_vecObjs[i] != nullptr)
			{
				_vecObjs[i]->stateController->currentState->animationController.NextTileIndex();
			}
		}
	}

	void FightersGroup::RenderObjPosition()
	{
		for (size_t i = 0; i < _vecObjs.size(); i++)
		{
			GameObj& obj = *_vecObjs[i];

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
		for (int32_t i = 0; i < _vecObjs.size(); i++)
		{
			_vecObjs[i]->stateController->currentState->RenderColliderQuads(*_camera);
		}
	}
	
	void FightersGroup::SetFighterInfo(olc::vi2d _startingPos, PlayerType _playerType)
	{
		_vecObjs.push_back(new GameObj());
		_vecObjs.back()->objData.SetCreationID(_vecObjs.size());
		_vecObjs.back()->objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		_vecObjs.back()->objData.SetPosition(_startingPos);
		_vecObjs.back()->objData.SetPlayerType(_playerType);
	}

	ObjData* FightersGroup::GetObjData(int32_t index)
	{
		if (index >= _vecObjs.size())
		{
			return nullptr;
		}
		else
		{
			return &_vecObjs[index]->objData;
		}
	}
}