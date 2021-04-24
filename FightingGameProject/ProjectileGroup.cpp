#include "ProjectileGroup.h"

namespace RB
{
	ProjectileGroup::ProjectileGroup()
	{
		ptrAnimationRenderer = new AnimationRenderer();
	}

	ProjectileGroup::~ProjectileGroup()
	{
		delete ptrAnimationRenderer;

		if (vecObjs.size() != 0)
		{
			IF_COUT{ std::cout << std::endl; };

			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				IF_COUT{ std::cout << "destructing projectile: " << vecObjs[i]->objData.GetCreationID() << std::endl; };
				delete vecObjs[i];
			}

			IF_COUT{ std::cout << std::endl; };
		}
	}

	void ProjectileGroup::UpdateStates(GameData& gameData)
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				GameObj& obj = *vecObjs[i];
				State* state = vecObjs[i]->stateController.currentState;

				if (state != nullptr)
				{
					state->RunUpdateProcess(vecObjs[i]->objData, gameData);
				}
			}
		}
	}

	void ProjectileGroup::RenderObjPosition(Camera& cam)
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				vecObjs[i]->objData.objBoxCollider.Render(cam, vecObjs[i]->objData.GetPosition(), olc::CYAN);
			}
		}
	}

	void ProjectileGroup::RenderStates(Camera& cam, bool update)
	{
		for (size_t i = 0; i < vecObjs.size(); i++)
		{
			if (vecObjs[i] != nullptr)
			{
				ptrAnimationRenderer->RenderComponent(vecObjs[i], cam);

				if (update)
				{
					vecObjs[i]->stateController.currentState->animationController.NextTileIndex();
				}
			}
		}
	}

	void ProjectileGroup::RenderBoxColliders(Camera& cam)
	{

	}

	olc::vi2d ProjectileGroup::GetObjWorldPos(size_t index)
	{
		if (index < vecObjs.size())
		{
			if (vecObjs[index] != nullptr)
			{
				return vecObjs[index]->objData.GetPosition();
			}
		}

		return { 0, 0 };
	}

	olc::vi2d ProjectileGroup::GetObjBoxColliderWorldPos(size_t index)
	{
		if (index < vecObjs.size())
		{
			if (vecObjs[index] != nullptr)
			{
				olc::vi2d relativePos = vecObjs[index]->objData.objBoxCollider.RelativePosition();
				olc::vi2d worldPos = relativePos + vecObjs[index]->objData.GetPosition();
				return worldPos;
			}
		}

		return { 0, 0 };
	}

	std::array<olc::vi2d, 4> ProjectileGroup::GetObjBoxColliderWorldQuad(size_t index)
	{
		std::array<olc::vi2d, 4> arr;

		if (index < vecObjs.size())
		{
			if (vecObjs[index] != nullptr)
			{
				arr[0] = vecObjs[index]->objData.objBoxCollider.RelativePoint0();
				arr[1] = vecObjs[index]->objData.objBoxCollider.RelativePoint1();
				arr[2] = vecObjs[index]->objData.objBoxCollider.RelativePoint2();
				arr[3] = vecObjs[index]->objData.objBoxCollider.RelativePoint3();

				olc::vi2d relativePos = vecObjs[index]->objData.objBoxCollider.RelativePosition();

				arr[0] += relativePos;
				arr[1] += relativePos;
				arr[2] += relativePos;
				arr[3] += relativePos;

				olc::vi2d playerPos = vecObjs[index]->objData.GetPosition();

				arr[0] += playerPos;
				arr[1] += playerPos;
				arr[2] += playerPos;
				arr[3] += playerPos;
			}
		}

		return arr;
	}

	size_t ProjectileGroup::GetObjCount()
	{
		return vecObjs.size();
	}

	size_t ProjectileGroup::GetObjCreationID(size_t index)
	{
		if (index < vecObjs.size())
		{
			if (vecObjs[index] != nullptr)
			{
				return vecObjs[index]->objData.GetCreationID();
			}
		}

		return 0;
	}

	void ProjectileGroup::DeleteObj(size_t index)
	{
		delete vecObjs[index];
		vecObjs[index] = nullptr;

		vecObjs.erase(vecObjs.begin() + index);
	}

	size_t ProjectileGroup::GetOwnerCreationID(size_t index)
	{
		if (index < vecObjs.size())
		{
			if (vecObjs[index] != nullptr)
			{
				return vecObjs[index]->objData.GetOwnerID();
			}
		}

		return 0;
	}

	void ProjectileGroup::CreateProjectiles(std::vector<CreateProjectile>& vecSpecs)
	{
		for (size_t i = 0; i < vecSpecs.size(); i++)
		{
			GameObj* obj = _Create();

			if (vecSpecs[i].projectileType == ProjectileType::HADOUKEN)
			{
				obj->stateController.currentState = State::NewState<Hadouken_MoveForward>();
			}

			if (vecSpecs[i].forward.x < 0)
			{
				obj->objData.FaceRight(false);
			}
			else if (vecSpecs[i].forward.x > 0)
			{
				obj->objData.FaceRight(true);
			}

			obj->objData.SetPosition(vecSpecs[i].startPos);
			obj->objData.SetOwnerID(vecSpecs[i].ownerObjCreationID);

			vecObjs.push_back(obj);
		}
	}

	GameObj* ProjectileGroup::_Create()
	{
		creationCount++;
		GameObj* obj = new GameObj(creationCount);
		return obj;
	}
}