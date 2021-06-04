#pragma once
#include <vector>
#include "GameObj.h"

namespace RB
{
	class PlayerToProjectileCollision
	{
	private:
		std::vector<GameObj*>* _vecFighters = nullptr;
		std::vector<GameObj*>* _vecProjectiles = nullptr;

	public:
		PlayerToProjectileCollision(std::vector<GameObj*>* fighters, std::vector<GameObj*>* projectiles)
		{
			_vecFighters = fighters;
			_vecProjectiles = projectiles;
		}
	};
}