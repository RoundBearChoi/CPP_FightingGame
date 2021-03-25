#pragma once
#include <iostream>
#include "DevSettings.h"
#include "ObjData.h"
#include "GameData.h"
#include "AnimationController.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "SpriteLoader.h"
#include "PlayerInput.h"
#include "Directions.h"
#include "CollisionCheck.h"

namespace RB
{
	class State
	{
	protected:
		bool isNew = true;

		void MakeHash(size_t& _hash)
		{
			IF_COUT{ std::cout << "hashing: " << animationController.GetSpritePath() << std::endl; }
			_hash = std::hash<std::string>{}(animationController.GetSpritePath());
			IF_COUT{ std::cout << _hash << std::endl; };
		}

		virtual size_t& Hash()
		{
			static size_t defaultHash = 0;
			return defaultHash;
		}

	public:
		State* nextState = nullptr;
		AnimationController animationController;
		std::vector<CollisionCheck> vecCollisionCheck;

		virtual ~State() {};
		virtual void OnEnter(ObjData& objData, GameData& gameData) = 0;
		virtual void UpdateState(ObjData& objData, GameData& gameData) = 0;
		
		virtual void OnAnimationUpdate(ObjData& objData, GameData& gameData) 
		{

		};

		virtual std::vector<BoxCollider>& GetColliders()
		{
			static std::vector<BoxCollider> defaultVec;
			return defaultVec;
		}

		virtual std::vector<olc::vi2d>& GetColliderQuads()
		{
			static std::vector<olc::vi2d> defaultVec;
			return defaultVec;
		}

		size_t GetHash()
		{
			size_t& h = Hash();

			if (h == 0)
			{
				MakeHash(h);
			}
			
			return h;
		}
		
		void UpdateColliders()
		{
			std::vector<BoxCollider>& vec = GetColliders();
			std::vector<olc::vi2d>& vecQuads = GetColliderQuads();

			if (vec.size() == 0)
			{
				ColliderLoader::SetFighterBodyParts(vec, animationController.GetTotalTiles());
				ColliderLoader::LoadColliderData(vec, animationController.GetColliderPath());

				vecQuads.clear();
				vecQuads.reserve(vec.size() * 4);

				for (size_t i = 0; i < vec.size(); i++)
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

		void RenderColliderQuads(ObjData& objData, Camera& cam)
		{
			std::vector<olc::vi2d>& quads = GetColliderQuads();

			if (quads.size() == 0)
			{
				return;
			}

			int32_t start = animationController.status.nCurrentTile * (4 * ColliderLoader::TotalBodyParts());

			for (size_t i = start; i < start + (4 * ColliderLoader::TotalBodyParts()); i += 4)
			{
				olc::vi2d playerPos = objData.GetPosition();

				//get worldpos from quad specs
				std::array<olc::vi2d, 4>worldPos;
				worldPos[0] = quads[i];
				worldPos[1] = quads[i + 1];
				worldPos[2] = quads[i + 2];
				worldPos[3] = quads[i + 3];

				if (!objData.IsFacingRight())
				{
					worldPos[0].x *= -1;
					worldPos[1].x *= -1;
					worldPos[2].x *= -1;
					worldPos[3].x *= -1;
				}

				worldPos[0] += playerPos;
				worldPos[1] += playerPos;
				worldPos[2] += playerPos;
				worldPos[3] += playerPos;

				//convert to screenpos
				std::array<olc::vf2d, 4>render;
				render[0] = RelativeVector::GetPosition(worldPos[0], cam);
				render[1] = RelativeVector::GetPosition(worldPos[1], cam);
				render[2] = RelativeVector::GetPosition(worldPos[2], cam);
				render[3] = RelativeVector::GetPosition(worldPos[3], cam);

				//lines
				olc::Renderer::ptrPGE->DrawLine(render[0], render[1], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(render[1], render[2], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(render[2], render[3], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(render[3], render[0], olc::BLUE);

				//transparent sprites
				DebugRenderer::RenderBox(render);
			}
		}

		void UnloadColliderData()
		{
			std::vector<BoxCollider>& col = GetColliders();
			col.clear();
		}
	};
}