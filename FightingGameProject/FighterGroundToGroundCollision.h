#pragma once
#include <array>
#include "GameObj.h"
#include "RandomInteger.h"
#include "AABB.h"
#include "Normalize.h"

namespace RB
{
	class FighterGroundToGroundCollision
	{
	private:
		RandomInteger randomInteger;

	public:
		void Update(std::array<GameObj, 2>& arrObjs)
		{
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
	};
}