#include "AnimationController.h"

namespace RB
{
	void AnimationController::SetParams(SpriteType _spriteType, int32_t _decalTypeIndex, int32_t _totalWith, int32_t _totalHeight, int32_t _tileCountX, int32_t _tileCountY, int32_t _totalTileCount)
	{
		status.spriteType = _spriteType;
		status.decalTypeIndex = _decalTypeIndex;

		specs.totalWidth = _totalWith;
		specs.totalHeight = _totalHeight;
		specs.tileCountX = _tileCountX;
		specs.tileCountY = _tileCountY;
		specs.totalTiles = _totalTileCount;
	}

	void AnimationController::SetColliderQuads(std::vector<BoxCollider>& vec)
	{
		vecColliderQuads.reserve(vec.size() * 4);

		for (int i = 0; i < vec.size(); i++)
		{
			vec[i].SetQuad();
			vec[i].UpdateRotation();

			vecColliderQuads.push_back(vec[i].Point0());
			vecColliderQuads.push_back(vec[i].Point1());
			vecColliderQuads.push_back(vec[i].Point2());
			vecColliderQuads.push_back(vec[i].Point3());
		}
	}

	void AnimationController::UpdateTileIndex(bool ignoreDelay)
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