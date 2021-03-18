#pragma once
#include "olcPixelGameEngine.h"
#include "OffsetType.h"

namespace RB
{
	class ObjData
	{
	private:
		olc::vi2d position = { 0, 0 };
		olc::vi2d spriteSize = { 0, 0 };
		size_t creationID = 0;
		OffsetType offsetType = OffsetType::NONE;
		int32_t currentAnimationIndex = 0;

	public:
		olc::vi2d GetPosition() { return position; }
		void SetPosition(olc::vi2d _pos) { position = _pos; }

		olc::vi2d GetSpriteSize() { return spriteSize; }
		void SetSpriteSize(olc::vi2d _size) { spriteSize = _size; }

		size_t GetCreationID() { return creationID;	}
		void SetCreationID(size_t t) { creationID = t; }

		OffsetType GetOffsetType() { return offsetType; }
		void SetOffsetType(OffsetType _type) { offsetType = _type; }

		int32_t GetAnimationIndex() { return currentAnimationIndex; }
		void SetAnimationIndex(int32_t _int) { currentAnimationIndex = _int; }
	};
}
