#include "State.h"

namespace RB
{
	State::~State()
	{

	}

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

	void State::RunUpdateProcess()
	{
		if (IsNew())
		{
			OnEnter();
		}

		OnUpdate();
		stateUpdateCount++;

		if (animationController.status.nDelayCount == 0)
		{
			OnAnimationUpdate();
		}
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

	void State::UpdateColliderParts()
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
				vec[i].SetQuad(OffsetType::CENTER_CENTER);
				vec[i].UpdateRotation();

				vecQuads.push_back(vec[i].RelativePoint0());
				vecQuads.push_back(vec[i].RelativePoint1());
				vecQuads.push_back(vec[i].RelativePoint2());
				vecQuads.push_back(vec[i].RelativePoint3());
			}
		}
	}

	void State::RenderColliderQuads(Camera& cam)
	{
		if (DevSettings::renderMode == RenderMode::SPRITES_ONLY)
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
			olc::vi2d playerPos = _ownerObj->objData.GetPosition();

			//get worldpos from quad specs
			std::array<olc::vi2d, 4>worldPos;
			worldPos[0] = quads[i];
			worldPos[1] = quads[i + 1];
			worldPos[2] = quads[i + 2];
			worldPos[3] = quads[i + 3];

			if (!_ownerObj->objData.IsFacingRight())
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
			render[0] = ScreenVector::GetScreenPosition(worldPos[0], cam);
			render[1] = ScreenVector::GetScreenPosition(worldPos[1], cam);
			render[2] = ScreenVector::GetScreenPosition(worldPos[2], cam);
			render[3] = ScreenVector::GetScreenPosition(worldPos[3], cam);

			//lines
			olc::Renderer::ptrPGE->DrawLine(render[0], render[1], olc::BLUE);
			olc::Renderer::ptrPGE->DrawLine(render[1], render[2], olc::BLUE);
			olc::Renderer::ptrPGE->DrawLine(render[2], render[3], olc::BLUE);
			olc::Renderer::ptrPGE->DrawLine(render[3], render[0], olc::BLUE);

			//transparent sprites
			BoxRenderer::Render(render, olc::RED);
		}
	}

	void State::UnloadColliderData()
	{
		std::vector<BoxCollider>& col = GetColliders();
		col.clear();
	}

	olc::vi2d State::GetColliderWorldPos(BodyType _bodyType)
	{
		std::vector<BoxCollider>& vec = GetColliders();

		size_t index = animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts() + (int32_t)_bodyType;

		if (index < vec.size())
		{
			olc::vi2d relativePos = vec[index].RelativePosition();

			if (!_ownerObj->objData.IsFacingRight())
			{
				relativePos.x *= -1;
			}

			olc::vi2d worldPos = relativePos + _ownerObj->objData.GetPosition();

			return worldPos;
		}
		else
		{
			return olc::vi2d(0, 0);
		}
	}

	std::array<olc::vi2d, 4> State::GetColliderQuadsWorldPos(BodyType _bodyType)
	{
		std::vector<olc::vi2d>& vec = GetColliderQuads();

		size_t start = animationController.status.nCurrentTile * (4 * ColliderLoader::TotalBodyParts());
		start += ((size_t)_bodyType * 4);

		std::array<olc::vi2d, 4> arr;

		arr[0] = vec[start];
		arr[1] = vec[start + 1];
		arr[2] = vec[start + 2];
		arr[3] = vec[start + 3];

		if (!_ownerObj->objData.IsFacingRight())
		{
			arr[0].x *= -1;
			arr[1].x *= -1;
			arr[2].x *= -1;
			arr[3].x *= -1;
		}

		arr[0] += _ownerObj->objData.GetPosition();
		arr[1] += _ownerObj->objData.GetPosition();
		arr[2] += _ownerObj->objData.GetPosition();
		arr[3] += _ownerObj->objData.GetPosition();

		return arr;
	}

	CheckCollisionMessage* State::GetCheckCollisionMessage()
	{
		return bodyToBodyCollisions.GetCheckCollisionMessage(animationController);
	}
}