#pragma once
#include "olcPixelGameEngine.h"
#include "ObjData.h"
#include "BoxCollider.h"
#include "BottomSegments.h"

namespace RB
{
	class CollisionData
	{
	private:
		ObjData* _objData = nullptr;

	public:
		BoxCollider objBoxCollider;
		MoveSegments* moveSegments = nullptr;

		CollisionData(ObjData* objData)
		{
			_objData = objData;
			moveSegments = new MoveSegments(objData, &objBoxCollider);
		}

		~CollisionData()
		{
			delete (moveSegments);
		}
	};
}