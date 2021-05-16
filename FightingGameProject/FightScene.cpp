#include "FightScene.h"

namespace RB
{
	class Fighter_0_Idle;

	FightScene::FightScene()
	{
		IF_COUT{ std::cout << "constructing FightScene" << std::endl; };

		_fighters = new FightersGroup();
		_projectiles = new ProjectileGroup();
		_impactEffects = new ImpactEffectsGroup();
		_cam = new Camera();

		_slowMotion = new SlowMotion(_fighters);
		
		DevSettings::renderMode = RenderMode::SPRITES_ONLY;
	}

	FightScene::~FightScene()
	{
		IF_COUT{ std::cout << "destructing FightScene" << std::endl; };

		delete _fighters;
		delete _projectiles;
		delete _impactEffects;
		delete _slowMotion;

		if (_damageDetector != nullptr)
		{
			delete _damageDetector;
		}
	}

	void FightScene::InitScene()
	{
		_fighters->SetFighterInfo(olc::vi2d(-100, 0), PlayerType::PLAYER_1);
		_fighters->SetFighterInfo(olc::vi2d(100, 0), PlayerType::PLAYER_2);

		_fighters->SetState(0, State::NewState<Fighter_0_Idle>(_fighters->GetObjData(0)));
		_fighters->SetState(1, State::NewState<Fighter_0_Idle>(_fighters->GetObjData(1)));

		_damageDetector = new DamageDetector(_fighters, _projectiles, _impactEffects);
	}

	void FightScene::UpdateScene()
	{
		_damageDetector->Update();

		if (!_slowMotion->SkipUpdate())
		{
			_fighters->UpdateStates();
		}
		
		_impactEffects->UpdateStates();

		std::vector<CreateProjectileMessage>* p1 = _fighters->GetProjectileQueues(0);
		std::vector<CreateProjectileMessage>* p2 = _fighters->GetProjectileQueues(1);
		_projectiles->CreateProjectiles(*p1);
		_projectiles->CreateProjectiles(*p2);
		p1->clear();
		p2->clear();

		_projectiles->UpdateStates();
	}

	void FightScene::RenderObjs()
	{
		ShowZeroPosition(*_cam);

		_fighters->RenderObjPosition(*_cam);
		_fighters->RenderComponents();
		_projectiles->RenderObjPosition(*_cam);
		_impactEffects->RenderObjPosition(*_cam);
	}

	void FightScene::RenderStates(bool update)
	{
		_fighters->RenderStates(*_cam, update);
		_fighters->RenderBoxColliders(*_cam);
		_projectiles->RenderStates(*_cam, update);
		_impactEffects->RenderStates(*_cam, update);
	}
}