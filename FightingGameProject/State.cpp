#include "State.h"

namespace RB
{
	size_t& State::Hash()
	{
		static size_t defaultHash = 0;
		return defaultHash;
	}

	void State::MakeHash(size_t& _hash)
	{
		IF_COUT{ std::cout << "hashing: " << animationController.GetSpritePath() << std::endl; }
		_hash = std::hash<std::string>{}(animationController.GetSpritePath());
		IF_COUT{ std::cout << _hash << std::endl; };
	}

	std::vector<BoxCollider>& State::GetColliders()
	{
		static std::vector<BoxCollider> defaultVec;
		return defaultVec;
	}

	std::vector<olc::vi2d>& State::GetColliderQuads()
	{
		static std::vector<olc::vi2d> defaultVec;
		return defaultVec;
	}

	size_t State::GetHash()
	{
		size_t& h = Hash();

		if (h == 0)
		{
			MakeHash(h);
		}

		return h;
	}

	void State::UpdateColliders()
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

	bool State::IsNew()
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

	void State::RenderColliderQuads(ObjData& objData, Camera& cam)
	{
		if (!DevSettings::renderDebugBoxes)
		{
			return;
		}

		std::vector<olc::vi2d>& quads = GetColliderQuads();

		if (quads.size() == 0)
		{
			return;
		}

		size_t start = animationController.status.nCurrentTile * (4 * ColliderLoader::TotalBodyParts());

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

	void State::UnloadColliderData()
	{
		std::vector<BoxCollider>& col = GetColliders();
		col.clear();
	}

	CollisionStatus* State::GetCollisionStatus()
	{
		//collision check
		for (size_t i = 0; i < vecCollisionStatus.size(); i++)
		{
			if (vecCollisionStatus[i].frame == animationController.status.nCurrentTile)
			{
				return &vecCollisionStatus[i];
			}
		}

		return nullptr;
	}

	olc::vi2d State::GetColliderWorldPos(BodyType _bodyType, ObjData& objData)
	{
		std::vector<BoxCollider>& vec = GetColliders();

		size_t index = animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts() + (int32_t)_bodyType;

		if (index < vec.size())
		{
			olc::vi2d pos = vec[index].Position();

			if (!objData.IsFacingRight())
			{
				pos.x *= -1;
			}

			pos += objData.GetPosition();

			return pos;
		}
		else
		{
			return olc::vi2d(0, 0);
		}
	}

	std::array<olc::vi2d, 4> State::GetColliderQuadsWorldPos(BodyType _bodyType, ObjData& objData)
	{
		std::vector<olc::vi2d>& vec = GetColliderQuads();

		size_t start = animationController.status.nCurrentTile * (4 * ColliderLoader::TotalBodyParts());
		start += ((size_t)_bodyType * 4);

		std::array<olc::vi2d, 4> arr;

		arr[0] = vec[start];
		arr[1] = vec[start + 1];
		arr[2] = vec[start + 2];
		arr[3] = vec[start + 3];

		if (!objData.IsFacingRight())
		{
			arr[0].x *= -1;
			arr[1].x *= -1;
			arr[2].x *= -1;
			arr[3].x *= -1;
		}

		arr[0] += objData.GetPosition();
		arr[1] += objData.GetPosition();
		arr[2] += objData.GetPosition();
		arr[3] += objData.GetPosition();

		return arr;
	}
}