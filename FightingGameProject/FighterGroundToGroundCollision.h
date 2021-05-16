#pragma once
#include <array>
#include "IGroupComponent.h"
#include "RandomInteger.h"
#include "AABB.h"
#include "Normalize.h"

namespace RB
{
	class FighterGroundToGroundCollision : public IGroupComponent
	{
	private:
		std::vector<GameObj*>* _vecFighters = nullptr;
		RandomInteger randomInteger;

	public:
		FighterGroundToGroundCollision(std::vector<GameObj*>* vecFighters)
		{
			_vecFighters = vecFighters;
		}

		void Update() override
		{
			std::vector<GameObj*>& vec = *_vecFighters;

			//ground vs ground
			if (vec[0]->objData.GetPosition().y == 0 && vec[1]->objData.GetPosition().y == 0)
			{
				//fighters shouldn't have same position
				int32_t distance = std::abs(vec[0]->objData.GetPosition().x - vec[1]->objData.GetPosition().x);
				if (distance <= 1)
				{
					int index = randomInteger.GetInteger(0, 1);
					olc::vi2d newPos = vec[index]->objData.GetPosition() + olc::vi2d(10, 0);
					vec[index]->objData.SetPosition(newPos);

					IF_COUT{ std::cout << "distance between fighters: " << distance << std::endl; };
					IF_COUT{ std::cout << "resolving same position" << std::endl; };
					IF_COUT{ std::cout << "random index: " << index << std::endl; };
				}

				if (AABB::IsColliding(
					vec[0]->objData.objBoxCollider, vec[0]->objData.GetPosition(), //p1 obj boxcollider
					vec[1]->objData.objBoxCollider, vec[1]->objData.GetPosition())) //p2 obj boxcollider
				{
					olc::vi2d relMidPoint = vec[1]->objData.GetPosition() - vec[0]->objData.GetPosition();
					relMidPoint.x = (int32_t)std::round(relMidPoint.x / 2.0f);
					relMidPoint.y = (int32_t)std::round(relMidPoint.y / 2.0f);
					olc::vf2d midPoint = vec[0]->objData.GetPosition() + relMidPoint;

					olc::vi2d p1Dir = vec[0]->objData.GetPosition() - midPoint;
					olc::vi2d p2Dir = vec[1]->objData.GetPosition() - midPoint;

					olc::vf2d p1rel = (olc::vf2d)Normalize::Norm(p1Dir) * (float)vec[0]->objData.objBoxCollider.Width() / 2.0f;
					olc::vf2d p2rel = (olc::vf2d)Normalize::Norm(p2Dir) * (float)vec[1]->objData.objBoxCollider.Width() / 2.0f;

					olc::vf2d p1Resolved = midPoint + p1rel;
					olc::vf2d p2Resolved = midPoint + p2rel;

					olc::vi2d p1Rounded{ 0, 0 };
					olc::vi2d p2Rounded{ 0, 0 };

					p1Rounded.x = (int32_t)std::round(p1Resolved.x);
					p2Rounded.x = (int32_t)std::round(p2Resolved.x);

					vec[0]->objData.SetPosition(p1Rounded);
					vec[1]->objData.SetPosition(p2Rounded);
				}
			}
		}
	};
}