#pragma once

namespace RB
{
	class ColliderData
	{
	private:
		std::vector<GameObj*>* _vecObjs = nullptr;

	public:
		ColliderData(std::vector<GameObj*>* vecObjs)
		{
			_vecObjs = vecObjs;
		}

		olc::vi2d GetBoxColliderWorldPos(size_t index)
		{
			std::vector<GameObj*>& vec = *_vecObjs;

			if (index < vec.size())
			{
				if (vec[index] != nullptr)
				{
					olc::vi2d relativePos = vec[index]->objData.objBoxCollider.RelativePosition();
					olc::vi2d worldPos = relativePos + vec[index]->objData.GetPosition();
					return worldPos;
				}
			}

			return olc::vi2d(0, 0);
		}

		std::array<olc::vi2d, 4> GetBoxColliderWorldQuad(size_t index)
		{
			std::vector<GameObj*>& vec = *_vecObjs;
			std::array<olc::vi2d, 4> arr;

			if (index < vec.size())
			{
				if (vec[index] != nullptr)
				{
					arr[0] = vec[index]->objData.objBoxCollider.RelativePoint0();
					arr[1] = vec[index]->objData.objBoxCollider.RelativePoint1();
					arr[2] = vec[index]->objData.objBoxCollider.RelativePoint2();
					arr[3] = vec[index]->objData.objBoxCollider.RelativePoint3();

					olc::vi2d relativePos = vec[index]->objData.objBoxCollider.RelativePosition();

					arr[0] += relativePos;
					arr[1] += relativePos;
					arr[2] += relativePos;
					arr[3] += relativePos;

					olc::vi2d playerPos = vec[index]->objData.GetPosition();

					arr[0] += playerPos;
					arr[1] += playerPos;
					arr[2] += playerPos;
					arr[3] += playerPos;
				}
			}

			return arr;
		}

		olc::vi2d GetBodyWorldPos(int32_t index, BodyType bodyType)
		{
			std::vector<GameObj*>& vec = *_vecObjs;

			if (index < vec.size())
			{
				State* state = vec[index]->stateController->currentState;

				if (state != nullptr)
				{
					return state->GetColliderWorldPos(bodyType);
				}
			}

			return { 0, 0 };
		}

		std::array<olc::vi2d, 4> GetBodyWorldQuad(int32_t index, BodyType bodyType)
		{

		}
	};
}