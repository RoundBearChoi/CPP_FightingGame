#pragma once
#include "AnimationSpecs.h"
#include "AnimationStatus.h"
#include "SpriteType.h"

namespace RB
{
	class AnimationController
	{
	private:
		AnimationSpecs specs;
		std::string collisionFileName = "none";
		
	public:
		AnimationStatus status;

		void SetCollisionFileName(std::string _name) { collisionFileName = _name; }
		std::string CollisionFileName() { return collisionFileName; }
		int32_t TotalTiles() { return specs.tileCountX * specs.tileCountY; }
		void SetParams(SpriteType _spriteType, int32_t _decalTypeIndex, int32_t _totalWith, int32_t _totalHeight, int32_t _tileCountX, int32_t _tileCountY, int32_t _totalTileCount);
		void UpdateTileIndex(bool ignoreDelay = false);
		AnimationStatus* GetStatus();
		bool OnLastAnimationFrame();
	};
}