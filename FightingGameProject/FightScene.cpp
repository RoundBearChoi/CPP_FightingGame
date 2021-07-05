#include "FightScene.h"

namespace RB
{
	FightScene::FightScene()
	{
		IF_COUT{ std::cout << "constructing FightScene" << std::endl; };

		_cam = new Camera();

		_fighters = new FightersGroup(_cam);
		_projectiles = new ProjectileGroup(_cam);
		_impactEffects = new ImpactEffectsGroup(_cam);
		
		DevSettings::renderMode = RenderMode::SPRITES_ONLY;
	}

	FightScene::~FightScene()
	{
		IF_COUT{ std::cout << "destructing FightScene" << std::endl; };

		delete _fighters;
		delete _projectiles;
		delete _impactEffects;

		delete _playerToPlayerCollision;
		delete _meleeReaction;
		delete _playerToProjectileCollision;
		delete _projectileCollisionReaction;
	}

	void FightScene::InitScene()
	{
		_fighters->SetFighterInfo(olc::vi2d(-100, 0), PlayerType::PLAYER_1);
		_fighters->SetFighterInfo(olc::vi2d(100, 0), PlayerType::PLAYER_2);

		_fighters->GetObj(0)->SetState(State::NewState<Fighter_0_Idle>(_fighters->GetObj(0)));
		_fighters->GetObj(1)->SetState(State::NewState<Fighter_0_Idle>(_fighters->GetObj(1)));

		_playerToPlayerCollision = new PlayerToPlayerCollision(_fighters->GetObj(0), _fighters->GetObj(1));
		_meleeReaction = new MeleeReaction(_fighters->GetObj(0), _fighters->GetObj(1), _impactEffects);

		_playerToProjectileCollision = new PlayerToProjectileCollision(_fighters->GetVecObjs(), _projectiles->GetVecObjs());
		_projectileCollisionReaction = new ProjectileCollisionReaction(_fighters, _projectiles, _impactEffects);
	}

	void FightScene::UpdateScene()
	{
		PlayerToProjectileCollisionResult projColResult0 = _playerToProjectileCollision->FighterCollidesWithProjectile(0);
		PlayerToProjectileCollisionResult projColResult1 = _playerToProjectileCollision->FighterCollidesWithProjectile(1);
		_projectileCollisionReaction->Update(0, projColResult0);
		_projectileCollisionReaction->Update(1, projColResult1);

		MeleeCollisionResult F0HitsF1 = _playerToPlayerCollision->Fighter0HitsFighter1();
		MeleeCollisionResult F1HitsF0 = _playerToPlayerCollision->Fighter1HitsFighter0();
		_meleeReaction->Update(1, F0HitsF1);
		_meleeReaction->Update(0, F1HitsF0);

		std::vector<CreateProjectileMessage>* p1 = &_fighters->GetObj(0)->stateController->currentState->vecCreateProjectiles;
		std::vector<CreateProjectileMessage>* p2 = &_fighters->GetObj(1)->stateController->currentState->vecCreateProjectiles;
		_projectiles->CreateProjectiles(*p1);
		_projectiles->CreateProjectiles(*p2);
		p1->clear();
		p2->clear();

		_fighters->UpdateStates();
		_impactEffects->UpdateStates();
		_projectiles->UpdateStates();
	}

	void FightScene::RenderObjs()
	{
		ShowZeroPosition(*_cam);

		_fighters->RenderObjPosition();
		_projectiles->RenderObjPosition();
		_impactEffects->RenderObjPosition();
	}

	void FightScene::RenderStates()
	{
		_fighters->RenderStates();
		_fighters->RenderBoxColliders();

		_projectiles->RenderStates();
		_impactEffects->RenderStates();
	}
}