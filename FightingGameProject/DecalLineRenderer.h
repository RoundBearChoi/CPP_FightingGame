#pragma once
#include <iostream>
#include "olcPixelGameEngine.h"
#include "SpriteLoader.h"
#include "SpriteType.h"

namespace RB
{
	class DecalLineRenderer
	{
	private:
		static std::string path;

	public:
		static size_t GetHash()
		{
			static size_t hash = 0;

			if (hash == 0)
			{
				hash = std::hash<std::string>{}(path);
			}

			return hash;
		}

		static void Draw(olc::vi2d from, olc::vi2d to, olc::Pixel tint)
		{
			olc::Decal* d = SpriteLoader::ptr->FindDecal(GetHash(), (int32_t)SpriteType::DEBUG_ELEMENTS);

			std::array<olc::vf2d, 4> points;
			points[0] = from;
			points[1] = from - olc::vi2d(0, -1);
			points[2] = to - olc::vi2d(0, -1);
			points[3] = to;

			olc::Renderer::ptrPGE->DrawWarpedDecal(d, points, tint);
		}
	};
}