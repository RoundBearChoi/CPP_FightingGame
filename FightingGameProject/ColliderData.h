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

		}

		olc::vi2d GetBodyWorldPos(int32_t index, BodyType bodyType)
		{

		}

		std::array<olc::vi2d, 4> GetBodyWorldQuad(int32_t index, BodyType bodyType)
		{

		}
	};
}