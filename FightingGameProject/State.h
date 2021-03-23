#pragma once
#include <iostream>
#include "DevSettings.h"
#include "ObjData.h"
#include "GameData.h"
#include "AnimationController.h"
#include "Renderer.h"
#include "SpriteLoader.h"

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
				ColliderLoader::LoadColliderData(vec, animationController.GetColliderPath());
			}

			if (vecQuads.size() == 0)
			{
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

				//IF_COUT
				//{
				//	for (size_t i = 0; i < vecQuads.size(); i++)
				//	{
				//		std::cout << "quads[" << i << "]" << vecQuads[i] << std::endl;
				//	} 
				//}
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

		void RenderColliderQuads(ObjData& objData, std::vector<olc::vi2d>& quads, Camera cam)
		{
			int32_t start = animationController.status.nCurrentTile * (4 * ColliderLoader::TotalBodyParts());

			for (size_t i = start; i < start + (4 * ColliderLoader::TotalBodyParts()); i += 4)
			{
				olc::vi2d playerPos = objData.GetPosition();

				std::array<olc::vf2d, 4>arr;
				arr[0] = RelativeVector::GetPosition(quads[i] + playerPos, cam);
				arr[1] = RelativeVector::GetPosition(quads[i + 1] + playerPos, cam);
				arr[2] = RelativeVector::GetPosition(quads[i + 2] + playerPos, cam);
				arr[3] = RelativeVector::GetPosition(quads[i + 3] + playerPos, cam);

				//lines
				olc::Renderer::ptrPGE->DrawLine(arr[0], arr[1], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(arr[1], arr[2], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(arr[2], arr[3], olc::BLUE);
				olc::Renderer::ptrPGE->DrawLine(arr[3], arr[0], olc::BLUE);

				//transparent sprites
				static size_t hash = 0;
				static olc::Decal* d = nullptr;

				if (hash == 0)
				{
					hash = std::hash<std::string>{}("PNG files/DebugElements/245whitesq_tr80.png");

					IF_COUT{ std::cout << "collider png hash: " << hash << std::endl; };
				}

				if (d == nullptr)
				{
					d = SpriteLoader::ptr->FindDecal(hash, (size_t)SpriteType::DEBUG_ELEMENTS);
				}
				else
				{
					RENDERER->DrawPartialWarpedDecal(d, arr, { 245, 245 }, { 0, 0 }, olc::RED);
				}
			}
		}
	};
}