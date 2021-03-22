#pragma once
#include <iostream>
#include "DevSettings.h"
#include "ObjData.h"
#include "GameData.h"
#include "AnimationController.h"

namespace RB
{
#define STATIC_VEC_COLLIDERS std::vector<BoxCollider>& GetColliders() { static std::vector<BoxCollider> vecColliders; return vecColliders; }
#define STATIC_VEC_COLLIDER_QUADS std::vector<olc::vi2d>& GetColliderQuads() { static std::vector<olc::vi2d> vecColliderQuads; return vecColliderQuads; }
	
	class State
	{
	protected:
		bool isNew = true;

		void MakeHash(size_t& _hash)
		{
			if (_hash == 0)
			{
				IF_COUT{ std::cout << "hashing: " << animationController.GetSpritePath() << std::endl; }
				_hash = std::hash<std::string>{}(animationController.GetSpritePath());
				IF_COUT{ std::cout << _hash << std::endl; };
			}
		}

	public:
		State* nextState = nullptr;
		AnimationController animationController;

		virtual size_t GetHash() = 0;
		virtual void OnEnter(ObjData& objData, GameData& gameData) = 0;
		virtual void UpdateState(ObjData& objData, GameData& gameData) = 0;
		virtual void RenderBoxColliders(ObjData& objData, Camera& cam) { }

		void UpdateColliders(std::vector<BoxCollider>& vec, std::vector<olc::vi2d>& vecQuads)
		{
			if (vec.size() == 0)
			{
				ColliderLoader::SetFighterBodyParts(vec, animationController.GetTotalTiles());
			}

			if (vecQuads.size() == 0)
			{
				vecQuads.reserve(vec.size() * 4);

				for (int i = 0; i < vec.size(); i++)
				{
					vec[i].SetQuad();
					vec[i].UpdateRotation();

					vecQuads.push_back(vec[i].Point0());
					vecQuads.push_back(vec[i].Point1());
					vecQuads.push_back(vec[i].Point2());
					vecQuads.push_back(vec[i].Point3());
				}
			}
		}

		bool IsNew()
		{
			if (isNew)
			{
				isNew = false;
				return true;
			}
			else
			{
				return false;
			}
		}

		template<class T>
		static State* NewState()
		{
			if (std::is_base_of<State, T>::value)
			{
				return new T();
			}
			else
			{
				return nullptr;
			}
		}
	};
}