#pragma once
#include "ObjGroup.h"
#include "GameObj.h"

//components
#include "AnimationRenderer.h"

//projectiles
#include "Hadouken_MoveForward.h"

namespace RB
{
	class ProjectileGroup : public ObjGroup
	{
	private:
		std::vector<GameObj*> vecObjs;
		size_t creationCount = 0;

		AnimationRenderer* ptrAnimationRenderer = nullptr;

	public:
		ProjectileGroup();
		~ProjectileGroup();

		void UpdateStates(GameData& gameData) override;
		void RenderObjPosition(Camera& cam) override;
		void RenderStates(Camera& cam, bool update) override;
		void RenderBoxColliders(Camera& cam) override;
		olc::vi2d GetObjWorldPos(size_t index) override;
		olc::vi2d GetObjBoxColliderWorldPos(size_t index) override;
		std::array<olc::vi2d, 4> GetObjBoxColliderWorldQuad(size_t index) override;
		size_t GetObjCount() override;
		size_t GetObjCreationID(size_t index) override;
		void DeleteObj(size_t index) override;
		size_t GetOwnerCreationID(size_t index) override;

		void CreateProjectiles(std::vector<CreateProjectile>& vecSpecs);
		GameObj* _Create();
	};
}