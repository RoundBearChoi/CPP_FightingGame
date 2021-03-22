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
		std::string colliderFile = "none";
		
	public:
		AnimationStatus status;
		std::vector<BoxCollider> vecColliders;

		void SetColliderFile(std::string _name) { colliderFile = _name; }
		std::string ColliderFile() { return colliderFile; }
		int32_t TotalTiles() { return specs.tileCountX * specs.tileCountY; }
		void SetParams(SpriteType _spriteType, int32_t _decalTypeIndex, int32_t _totalWith, int32_t _totalHeight, int32_t _tileCountX, int32_t _tileCountY, int32_t _totalTileCount);
		void SetColliders();
		void UpdateTileIndex(bool ignoreDelay = false);
		AnimationStatus* GetStatus();
		bool OnLastAnimationFrame();
	};
}