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
		ImpactEffectsGroup(Camera* camera);
		~ImpactEffectsGroup();

		void UpdateStates() override;
		void RenderStates() override;

		void RenderObjPosition() override;
		void RenderBoxColliders() override;

		void CreateObj(ObjType objType, olc::vi2d startPos) override;
	};
}