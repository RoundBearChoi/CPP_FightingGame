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

			//process jump
			if (obj.objData.ptrJumpProcessor != nullptr)
			{
				PlayerInput p = PlayerInput::Get(obj.objData.GetPlayerType(), gameData);
				Directions d = Directions::Get(obj.objData.IsFacingRight(), p);
				obj.objData.ptrJumpProcessor->UpdateJump(d.up, d.forward, d.back);

				if (obj.objData.GetPosition().y <= 0)
				{
					olc::vi2d vertical = obj.objData.GetPosition() - olc::vi2d(0, obj.objData.ptrJumpProcessor->GetUpForce());
					obj.objData.SetPosition(vertical);

					olc::vi2d horizontalForce = olc::vi2d{ 0, 0 };

					if (obj.objData.IsFacingRight())
					{
						horizontalForce = olc::vi2d(obj.objData.ptrJumpProcessor->GetSideForce(), 0);
					}
					else
					{
						horizontalForce = olc::vi2d(obj.objData.ptrJumpProcessor->GetSideForce() * -1, 0);
					}

					if (!obj.objData.ptrJumpProcessor->moveBack)
					{
						olc::vi2d horizontal = obj.objData.GetPosition() + horizontalForce;
						obj.objData.SetPosition(horizontal);
					}
					else
					{
						olc::vi2d horizontal = obj.objData.GetPosition() - horizontalForce;
						obj.objData.SetPosition(horizontal);
					}
				}
			}

			//clear jump
			if (obj.objData.GetPosition().y > 0)
			{
				olc::vi2d groundPos = olc::vi2d(obj.objData.GetPosition().x, 0);
				obj.objData.SetPosition(groundPos);

				delete obj.objData.ptrJumpProcessor;
				obj.objData.ptrJumpProcessor = nullptr;
			}
		}

		//resolve body mass collision

		//ground vs ground
		if (arrObjs[0].objData.GetPosition().y == 0 && arrObjs[1].objData.GetPosition().y == 0)
		{
			//fighters shouldn't have same position
			int32_t distance = std::abs(arrObjs[0].objData.GetPosition().x - arrObjs[1].objData.GetPosition().x);
			if (distance <= 1)
			{
				int index = randomInteger.GetInteger(0, 1);
				olc::vi2d newPos = arrObjs[index].objData.GetPosition() + olc::vi2d(10, 0);
				arrObjs[index].objData.SetPosition(newPos);

				IF_COUT{ std::cout << "distance between fighters: " << distance << std::endl; };
				IF_COUT{ std::cout << "resolving same position" << std::endl; };
				IF_COUT{ std::cout << "random index: " << index << std::endl; };
			}

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
			ptrAnimationRenderer->RenderComponent(&arrObjs[i], cam);

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
}