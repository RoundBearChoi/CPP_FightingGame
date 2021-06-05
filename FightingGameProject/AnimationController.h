#pragma once
#include "AnimationSpecs.h"
#include "AnimationStatus.h"
#include "SpriteType.h"
#include "BoxCollider.h"
#include "ColliderLoader.h"

namespace RB
{
	class AnimationController
	{
	private:
		AnimationSpecs specs;
		std::string colliderPath = "none";
		std::string spritePath = "none";

	public:
		AnimationStatus status;
		
		void SetColliderFile(std::string _name) { colliderPath = _name; }
		std::string GetColliderPath() { return colliderPath; }
		std::string GetSpritePath() { return spritePath; }
		void SetSpritePath(std::string str) { spritePath = str; }
		int32_t TotalTiles() { return specs.tileCountX * specs.tileCountY; }
		int32_t GetTotalTiles() { return specs.totalTiles; }
		
		void SetParams(SpriteType _spriteType, int32_t _totalWith, int32_t _totalHeight, int32_t _tileCountX, int32_t _tileCountY, int32_t _totalTileCount);
		void NextTileIndex();
		void ResetTileIndex();
		AnimationStatus* UpdateSource();
		bool OnLastAnimationFrame();
	};
}