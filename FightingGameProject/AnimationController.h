#pragma once
#include "AnimationSpecs.h"
#include "AnimationStatus.h"
#include "SpriteType.h"
#include "BoxCollider.h"
#include "ColliderLoader.h"
#include "Camera.h"

namespace RB
{
	class AnimationController
	{
	private:
		AnimationSpecs specs;
		std::string colliderFile = "none";
		std::string spritePath = "none";

	public:
		AnimationStatus status;
		
		void SetColliderFile(std::string _name) { colliderFile = _name; }
		std::string ColliderFile() { return colliderFile; }
		std::string GetSpritePath() { return spritePath; }
		void SetSpritePath(std::string str) { spritePath = str; }
		int32_t TotalTiles() { return specs.tileCountX * specs.tileCountY; }
		int32_t GetTotalTiles() { return specs.totalTiles; }
		
		void SetParams(SpriteType _spriteType, int32_t _decalTypeIndex, int32_t _totalWith, int32_t _totalHeight, int32_t _tileCountX, int32_t _tileCountY, int32_t _totalTileCount);
		void UpdateTileIndex(bool ignoreDelay = false);
		AnimationStatus* GetStatus();
		bool OnLastAnimationFrame();
		void RenderBoxColliders(Camera& cam);
	};
}