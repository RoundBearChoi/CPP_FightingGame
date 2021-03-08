#pragma once
#include "DevSettings.h"

namespace RB
{
	class GameObj
	{
	private:

	public:
		GameObj()
		{
			IF_COUT{ std::cout << "construcing GameObj" << std::endl; }
		}

		~GameObj()
		{
			IF_COUT{ std::cout << "destructing GameObj" << std::endl; }
		}

		void Render()
		{

		}

		bool IsCollidingAgainst(GameObj* _target)
		{
			//if (_target == nullptr)
			//{
			//	return false;
			//}
			//
			//if (_target->data.size.x <= 0.0f || _target->data.size.y <= 0.0f)
			//{
			//	return false;
			//}
			//
			//if (data.size.x <= 0.0f || data.size.y <= 0.0f)
			//{
			//	return false;
			//}
			//
			//olc::vf2d p1; //player top left position)
			//p1.x = _target->data.position.x - (_target->data.size.x / 2.0f);
			//
			//olc::vf2d p2; //shit top left position
			//p2.x = data.position.x - (data.size.x / 2.0f);
			//
			//if(p1.x < p2.x + data.size.x && p1.x + _target->data.size.x > p2.x)
			//{
			//	return true;
			//}

			return false;
		}
	};
}