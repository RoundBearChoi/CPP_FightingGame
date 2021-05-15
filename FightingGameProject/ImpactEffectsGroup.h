#pragma once
#include "ObjGroup.h"
#include "ObjType.h"
#include "ImpactEffect_Hit_0.h"
#include "GameDataFactory.h"

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

		void UpdateStates() override;
		void RenderStates(Camera& cam, bool update) override;

		void RenderObjPosition(Camera& cam) override;
		void RenderBoxColliders(Camera& cam) override;

		void CreateObj(ObjType objType, olc::vi2d startPos) override;
	};
}