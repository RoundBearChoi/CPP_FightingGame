#pragma once
#include "PlayerInput.h"
#include "ObjData.h"

namespace RB
{
	class Directions
	{
	public:
		bool forward = false;
		bool back = false;
		bool up = false;
		bool down = false;

		static Directions Get(ObjData& objData, PlayerInput& playerInput)
		{
			Directions d;

			if (objData.IsFacingRight())
			{
				if (playerInput.left && playerInput.right || !playerInput.left && !playerInput.right)
				{
					//double press
				}
				else if (playerInput.left)
				{
					d.back = true;
				}
				else if (playerInput.right)
				{
					d.forward = true;
				}
			}
			else
			{
				if (playerInput.left && playerInput.right || !playerInput.left && !playerInput.right)
				{
					//double press
				}
				else if (playerInput.left)
				{
					d.forward = true;
				}
				else if (playerInput.right)
				{
					d.back = true;
				}
			}

			if (playerInput.up)
			{
				d.up = true;
			}

			if (playerInput.down)
			{
				d.down = true;
			}

			return d;
		}

		static int32_t GetForwardSpeed(ObjData& objData, int32_t speed)
		{
			if (objData.IsFacingRight())
			{
				return speed;
			}
			else
			{
				return -speed;
			}
		}

		static int32_t GetBackSpeed(ObjData& objData, int32_t speed)
		{
			if (objData.IsFacingRight())
			{
				return -speed;
			}
			else
			{
				return speed;
			}
		}
	};
}