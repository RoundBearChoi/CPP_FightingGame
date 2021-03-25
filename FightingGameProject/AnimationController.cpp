#include "AnimationController.h"

namespace RB
{
	void AnimationController::SetParams(SpriteType _spriteType, int32_t _totalWith, int32_t _totalHeight, int32_t _tileCountX, int32_t _tileCountY, int32_t _totalTileCount)
	{
		status.spriteType = _spriteType;

		specs.totalWidth = _totalWith;
		specs.totalHeight = _totalHeight;
		specs.tileCountX = _tileCountX;
		specs.tileCountY = _tileCountY;
		specs.totalTiles = _totalTileCount;
	}

	void AnimationController::NextTileIndex(bool ignoreDelay)
	{
		if (!ignoreDelay)
		{
			status.nDelayCount++;

			if (status.nDelayCount >= status.nTransitionDelay)
			{
				status.nDelayCount = 0;
				status.nCurrentTile++;
			}
		}
		else
		{
			status.nCurrentTile++;
		}

		if (status.nCurrentTile >= specs.totalTiles)
		{
			if (status.bPlayOnce)
			{
				status.nCurrentTile = specs.totalTiles - 1;
			}
			else
			{
				status.nCurrentTile = 0;
			}
		}
	}

	AnimationStatus* AnimationController::GetStatus()
	{
		if (specs.tileCountX > 0 && specs.tileCountY > 0)
		{
			status.sourceSize.x = specs.totalWidth / specs.tileCountX;
			status.sourceSize.y = specs.totalHeight / specs.tileCountY;

			if (status.sourceSize.x != 0 && status.sourceSize.y > 0)
			{
				status.sourcePos.x = (status.nCurrentTile % specs.tileCountX) * status.sourceSize.x;
				status.sourcePos.y = (int32_t)floor(status.nCurrentTile / specs.tileCountX) * status.sourceSize.y;
			}

			return &status;
		}
		else
		{
			return nullptr;
		}
	}

	bool AnimationController::OnLastAnimationFrame()
	{
		if (status.nCurrentTile == specs.totalTiles - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}