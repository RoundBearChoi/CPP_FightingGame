#pragma once
#include "olcPixelGameEngine.h"
#include "SpriteLoader.h"

namespace RB
{
	class BoxRenderer
	{
	public:
		static void Render(std::array<olc::vf2d, 4>& points, olc::Pixel color)
		{
			static size_t hash = 0;
			static olc::Decal* d = nullptr;

			if (hash == 0)
			{
				hash = std::hash<std::string>{}("PNG files/DebugElements/1whitesq_tr80.png");

				IF_COUT{ std::cout << "collider png hash: " << hash << std::endl; };
			}

			if (d == nullptr)
			{
				d = SpriteLoader::ptr->FindDecal(hash, (size_t)SpriteType::DEBUG_ELEMENTS);
			}
			else
			{
				olc::Renderer::ptrPGE->DrawPartialWarpedDecal(d, points, { 245, 245 }, { 0, 0 }, color);
			}
		}
	};
}