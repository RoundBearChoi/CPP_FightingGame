#pragma once
#include "ObjGroup.h"
#include "ObjType.h"
#include "ImpactEffect_Hit_0.h"

//components
#include "AnimationRenderer.h"

namespace RB
{
	class ImpactEffectsGroup : public ObjGroup
	{
	private:
		AnimationRenderer* ptrAnimationRenderer = nullptr;

	public:
		ImpactEffectsGroup();
		~ImpactEffectsGroup();

		void UpdateStates(GameData& gameData) override;
		void RenderObjPosition(Camera& cam) override;
		void RenderStates(Camera& cam, bool update) override;
		void RenderBoxColliders(Camera& cam) override;
		size_t GetObjCount() override;
		size_t GetObjCreationID(size_t index) override;
		olc::vi2d GetObjWorldPos(size_t index) override;
		olc::vi2d GetObjBoxColliderWorldPos(size_t index) override;
		std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index) override;

		void CreateObj(ObjType objType, olc::vi2d startPos) override;
	};
}