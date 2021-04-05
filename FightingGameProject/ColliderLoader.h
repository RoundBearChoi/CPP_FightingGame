#pragma once
#include <vector>
#include "BoxCollider.h"
#include "BodyType.h"
#include "DevSettings.h"

namespace RB
{
	class ColliderLoader
	{
	public:
		static size_t TotalBodyParts()
		{
			return (size_t)BodyType::RIGHT_FOOT + 1;
		}

		static void SetFighterBodyParts(std::vector<BoxCollider>& vecColliders, size_t frames)
		{
			vecColliders.reserve(ColliderLoader::TotalBodyParts() * frames);

			for (int32_t i = 0; i < ColliderLoader::TotalBodyParts() * frames; i++)
			{
				int32_t x = (int32_t)floor(i / ColliderLoader::TotalBodyParts() * frames) * 1;
				int32_t y = -170 + (i % ColliderLoader::TotalBodyParts()) * 12;
				vecColliders.push_back(BoxCollider({ x, y }, 40, 50, 0.0f));
			}
		}

		static void LoadColliderData(std::vector<BoxCollider>& vecColliders, std::string colliderFileName)
		{
			std::string path = "BoxColliderData/";
			path += colliderFileName;

			IF_COUT{ std::cout << "loading collider: " << path << std::endl; };

			std::ifstream file(path);

			if (file.is_open())
			{
				size_t size = 0;
				file >> size;

				IF_COUT{ std::cout << "data size: " << size << std::endl; }
				IF_COUT{ std::cout << "collider size: " << vecColliders.size() << std::endl; }

					if (size == vecColliders.size())
					{
						for (size_t i = 0; i < vecColliders.size(); i++)
						{
							int32_t x = 0;
							int32_t y = 0;
							int32_t width = 0;
							int32_t height = 0;
							float rotation = 0.0f;

							file >> x;
							file >> y;
							file >> width;
							file >> height;
							file >> rotation;

							IF_COUT
							{
								std::cout << "vec[" << i << "]: " << x << ", " << y << ", " << width << ", " << height << ", " << rotation << std::endl;
							};

							vecColliders[i].SetPosition(x, y);
							vecColliders[i].SetWidth(width);
							vecColliders[i].SetHeight(height);
							vecColliders[i].SetRotation(rotation);
						}
					}

				file.close();
			}
		}

		static void SaveColliderData(std::vector<BoxCollider>& vecColliders, std::string colliderFileName)
		{
			std::string path = "BoxColliderData/";

			if (colliderFileName.compare("none") != 0)
			{
				path += colliderFileName;

				std::ofstream file(path);

				if (file.is_open())
				{
					size_t vecSize = vecColliders.size();

					IF_COUT{ std::cout << "vec size: " << vecSize << std::endl; }

					file << vecSize << std::endl;

					IF_COUT{ std::cout << "saving collider data.." << std::endl; }

					for (size_t i = 0; i < vecColliders.size(); i++)
					{
						int32_t x = vecColliders[i].RelativePosition().x;
						int32_t y = vecColliders[i].RelativePosition().y;
						int32_t width = vecColliders[i].Width();
						int32_t height = vecColliders[i].Height();
						float rotation = vecColliders[i].Rotation();

						file << x << std::endl;;
						file << y << std::endl;;
						file << width << std::endl;;
						file << height << std::endl;;
						file << rotation << std::endl;;

						IF_COUT
						{
							std::cout << "vec[" << i << "]: " << x << ", " << y << ", " << width << ", " << height << ", " << rotation << std::endl;
						};
					}

					file.flush();
					file.close();
				}
			}
		}
	};
}