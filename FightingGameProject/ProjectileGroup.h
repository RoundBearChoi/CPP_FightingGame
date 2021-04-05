#pragma once
#include "ObjGroup.h"
#include "GameObj.h"

//projectiles
#include "Hadouken_MoveForward.h"

namespace RB
{
	class ProjectileGroup : public ObjGroup
	{
	private:
		std::vector<GameObj*> vecObjs;
		size_t creationCount = 0;

	public:
		~ProjectileGroup()
		{
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

		void UpdateStates(GameData& gameData) override
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

		void RenderObjPosition(Camera& cam) override
		{
			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				if (vecObjs[i] != nullptr)
				{
					vecObjs[i]->objData.objBoxCollider.Render(cam, vecObjs[i]->objData.GetPosition(), olc::CYAN);
				}
			}
		}

		void RenderStates(Camera& cam, bool update) override
		{
			for (size_t i = 0; i < vecObjs.size(); i++)
			{
				if (vecObjs[i] != nullptr)
				{
					SheetRenderer::Render(vecObjs[i], cam);

					if (update)
					{
						vecObjs[i]->stateController.currentState->animationController.NextTileIndex();
					}
				}
			}
		}

		void RenderBoxColliders(Camera& cam) override
		{

		}

		olc::vi2d GetObjWorldPos(size_t index) override
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

		olc::vi2d GetObjBoxColliderWorldPos(size_t index) override
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

		std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index) override
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

		void CreateProjectiles(std::vector<CreateProjectile>& vecSpecs)
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

		size_t GetObjCount() override
		{
			return vecObjs.size();
		}

		GameObj* _Create()
		{
			creationCount++;
			GameObj* obj = new GameObj(creationCount);
			return obj;
		}
	};
}