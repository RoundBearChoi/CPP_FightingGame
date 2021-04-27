#pragma once
#include "olcPixelGameEngine.h"
#include "OffsetType.h"
#include "PlayerType.h"
#include "BoxCollider.h"
#include "JumpProcessor.h"

namespace RB
{
	class ObjData
	{
	private:
		olc::vi2d position = { 0, 0 };
		olc::vi2d spriteSize = { 0, 0 };
		size_t creationID = 0;
		size_t ownerID = 0;
		OffsetType offsetType = OffsetType::NONE;
		int32_t currentAnimationIndex = 0;
		bool onLeftSide = true;
		bool faceRight = true;
		PlayerType playerType = PlayerType::NONE;
		
	public:
		BoxCollider objBoxCollider;
		JumpProcessor* ptrJumpProcessor = nullptr;

		~ObjData();

		olc::vi2d GetPosition();
		void SetPosition(olc::vi2d _pos);

		olc::vi2d GetSpriteSize();
		void SetSpriteSize(olc::vi2d _size);

		size_t GetCreationID();
		void SetCreationID(size_t t);

		size_t GetOwnerID();
		void SetOwnerID(size_t t);

		OffsetType GetOffsetType();
		void SetOffsetType(OffsetType _type);

		int32_t GetAnimationIndex();
		void SetAnimationIndex(int32_t _int);

		void SetLeftSide(bool _left);
		bool IsOnLeftSide();

		void FaceRight(bool _faceRight);
		bool IsFacingRight();

		void SetPlayerType(PlayerType _playerType);
		PlayerType GetPlayerType();

		void CreateJumpProcessor();
	};
}