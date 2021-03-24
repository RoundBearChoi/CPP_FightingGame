#pragma once
#include "Renderer.h"
#include "SpriteLoader.h"

namespace RB
{
	class DebugRenderer
	{
	public:
		static void RenderBox(std::array<olc::vf2d, 4>& points)
		{
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
				RENDERER->DrawPartialWarpedDecal(d, points, { 245, 245 }, { 0, 0 }, olc::RED);
			}
		}
	};
}