#include "ObjData.h"

namespace RB
{
	ObjData::~ObjData()
	{
		if (ptrJumpProcessor != nullptr)
		{
			delete ptrJumpProcessor;
		}
	}

	olc::vi2d ObjData::GetPosition() { return position; }
	void ObjData::SetPosition(olc::vi2d _pos) { position = _pos; }

	olc::vi2d ObjData::GetSpriteSize() { return spriteSize; }
	void ObjData::SetSpriteSize(olc::vi2d _size) { spriteSize = _size; }

	size_t ObjData::GetCreationID() { return creationID; }
	void ObjData::SetCreationID(size_t t) { creationID = t; }

	size_t ObjData::GetOwnerID() { return ownerID; }
	void ObjData::SetOwnerID(size_t t) { ownerID = t; }

	OffsetType ObjData::GetOffsetType() { return offsetType; }
	void ObjData::SetOffsetType(OffsetType _type) { offsetType = _type; }

	int32_t ObjData::GetAnimationIndex() { return currentAnimationIndex; }
	void ObjData::SetAnimationIndex(int32_t _int) { currentAnimationIndex = _int; }

	void ObjData::SetLeftSide(bool _left) { onLeftSide = _left; }
	bool ObjData::IsOnLeftSide() { return onLeftSide; }

	void ObjData::FaceRight(bool _faceRight) { faceRight = _faceRight; }
	bool ObjData::IsFacingRight() { return faceRight; }

	void ObjData::SetPlayerType(PlayerType _playerType) { playerType = _playerType; }
	PlayerType ObjData::GetPlayerType() { return playerType; }

	void ObjData::UpdateFigherDirection(ObjData& enemy)
	{
		if (position.x < enemy.GetPosition().x)
		{
			onLeftSide = true;
		}
		else if (position.x > enemy.GetPosition().x)
		{
			onLeftSide = false;
		}
	}

	void ObjData::CreateJumpProcessor()
	{
		if (ptrJumpProcessor != nullptr)
		{
			delete ptrJumpProcessor;
		}

		ptrJumpProcessor = new JumpProcessor();
	}
}