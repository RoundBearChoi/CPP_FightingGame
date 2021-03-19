#pragma once
#include "AnimationSpecs.h"
#include "AnimationStatus.h"

namespace RB
{
	class AnimationController
	{
	private:
		AnimationSpecs specs;
		std::string collisionFileName = "testing";
		
	public:
		AnimationStatus status;

		void SetCollisionFileName(std::string _name) { collisionFileName = _name; }
		void SetParams(int32_t _decalTypeIndex, int32_t _totalWith, int32_t _totalHeight, int32_t _tileCountX, int32_t _tileCountY, int32_t _totalTileCount);
		void UpdateTileIndex(bool ignoreDelay = false);
		AnimationStatus* GetStatus();
		bool OnLastAnimationFrame();
	};
}