#pragma once
#include "AnimationSpecs.h"
#include "AnimationStatus.h"

namespace RB
{
	class AnimationController
	{
	private:
		AnimationSpecs specs;
		
	public:
		AnimationStatus status;

		void SetParams(int32_t _decalTypeIndex, int32_t _totalWith, int32_t _totalHeight, int32_t _tileCountX, int32_t _tileCountY, int32_t _totalTileCount);
		void UpdateTileIndex();
		AnimationStatus* GetStatus();
		bool OnLastAnimationFrame();
	};
}