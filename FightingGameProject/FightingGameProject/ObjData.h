#pragma once
#include "olcPixelGameEngine.h"
#include "OffsetType.h"

namespace RB
{
	class ObjData
	{
	private:
		olc::vf2d position = { 0.0f, 0.0f };
		olc::vf2d spriteSize = { 0.0f, 0.0f };
		size_t creationID = 0;
		OffsetType offsetType = OffsetType::NONE;

	public:
		olc::vf2d GetPosition() { return position; }
		void SetPosition(float _x, float _y) { position.x = _x; position.y = _y; }

		olc::vf2d GetSpriteSize() { return spriteSize; }
		void SetSpriteSize(float _x, float _y) { spriteSize.x = _x; spriteSize.y = _y; }

		size_t GetCreationID() { return creationID;	}
		void SetCreationID(size_t t) { creationID = t; }

		OffsetType GetOffsetType() { return offsetType; }
		void SetOffsetType(OffsetType _type) { offsetType = _type; }
	};
}