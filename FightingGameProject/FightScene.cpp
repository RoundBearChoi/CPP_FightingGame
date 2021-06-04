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

		//if (_damageDetector != nullptr)
		//{
		//	delete _damageDetector;
		//}

		delete _playerToPlayerCollision;
		delete _meleeReaction;
		delete _playerToProjectileCollision;
	}

	void FightScene::InitScene()
	{
		_fighters->SetFighterInfo(olc::vi2d(-100, 0), PlayerType::PLAYER_1);
		_fighters->SetFighterInfo(olc::vi2d(100, 0), PlayerType::PLAYER_2);

		_fighters->SetState(0, State::NewState<Fighter_0_Idle>(_fighters->GetObjData(0)));
		_fighters->SetState(1, State::NewState<Fighter_0_Idle>(_fighters->GetObjData(1)));

		//_damageDetector = new DamageDetector(_fighters, _projectiles, _impactEffects);

		_playerToPlayerCollision = new PlayerToPlayerCollision(_fighters->GetObj(0), _fighters->GetObj(1));
		_meleeReaction = new MeleeReaction(_fighters->GetObj(0), _fighters->GetObj(1), _impactEffects);

		_playerToProjectileCollision = new PlayerToProjectileCollision(_fighters->GetVecObjs(), _projectiles->GetVecObjs());
	}

	void FightScene::UpdateScene()
	{
		PlayerToProjectileCollisionResult projColResult0 = _playerToProjectileCollision->Fighter0_CollidesWithProjectile();
		PlayerToProjectileCollisionResult projColResult1 = _playerToProjectileCollision->Fighter1_CollidesWithProjectile();

		if (projColResult0.isCollided)
		{
			_projectiles->DeleteObj(projColResult0.projectileIndex);
			_fighters->GetObj(0)->SetNextState(State::NewState<Fighter_0_HitReaction_Side>(_fighters->GetObjData(0)));
			_impactEffects->CreateObj(ObjType::HIT_EFFECT_0, projColResult0.midPoint);
		}

		CollisionResult F0HitsF1 = _playerToPlayerCollision->Fighter0HitsFighter1();
		CollisionResult F1HitsF0 = _playerToPlayerCollision->Fighter1HitsFighter0();
		_meleeReaction->Update(1, F0HitsF1);
		_meleeReaction->Update(0, F1HitsF0);

		_fighters->UpdateStates();
		_impactEffects->UpdateStates();

		std::vector<CreateProjectileMessage>* p1 = _fighters->messageGetter->GetProjectileCreationMessage(0);
		std::vector<CreateProjectileMessage>* p2 = _fighters->messageGetter->GetProjectileCreationMessage(1);
		_projectiles->CreateProjectiles(*p1);
		_projectiles->CreateProjectiles(*p2);
		p1->clear();
		p2->clear();

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

	void FightScene::UpdateRenderTiles()
	{
		_fighters->UpdateSpriteTileIndex();
		_projectiles->UpdateSpriteTileIndex();
		_impactEffects->UpdateSpriteTileIndex();
	}
}