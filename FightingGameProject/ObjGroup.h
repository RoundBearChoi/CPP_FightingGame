#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "ObjType.h"
#include "GameObj.h"
#include "Camera.h"
#include "Updater.h"

namespace RB
{
	class ObjGroup
	{
	protected:
		std::vector<GameObj*> _vecObjs;
		Camera* _camera = nullptr;
		Updater* _updater = nullptr;

	public:
		virtual void UpdateStates() = 0;
		virtual void RenderStates() = 0;
		virtual void RenderObjPosition() = 0;
		virtual void RenderBoxColliders() = 0;

		virtual void UpdateSpriteTileIndex();

		virtual GameObj* GetObj(int32_t index);
		virtual ObjData* GetObjData(int32_t index);

		virtual void CreateObj(ObjType objType, olc::vi2d startPos) {}
		virtual void DeleteObj(size_t index);

		virtual std::vector<GameObj*>* GetVecObjs();
	};
}