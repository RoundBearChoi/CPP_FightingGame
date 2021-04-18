#pragma once
#include "PlayerInput.h"

namespace RB
{
	class Directions
	{
	public:
		bool forward = false;
		bool back = false;
		bool up = false;
		bool down = false;

		static Directions Get(bool isFacingRight, PlayerInput& playerInput)
		{
			Directions d;

			if (isFacingRight)
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

		static int32_t GetForwardSpeed(bool isFacingRight, int32_t speed)
		{
			if (isFacingRight)
			{
				return speed;
			}
			else
			{
				return -speed;
			}
		}

		static int32_t GetBackSpeed(bool isFacingRight, int32_t speed)
		{
			if (isFacingRight)
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