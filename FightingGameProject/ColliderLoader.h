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
		static int32_t TotalBodyParts()
		{
			return (int32_t)BodyType::RIGHT_FOOT + 1;
		}

		static void SetFighterBodyParts(std::vector<BoxCollider>& vecColliders, int32_t frames)
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

			IF_COUT{ std::cout << "loading collider data: " << colliderFileName << std::endl; }

			if (colliderFileName.compare("none") != 0)
			{
				path += colliderFileName;

				FILE* pFile;
				size_t size = 0;

#ifdef _WIN32
				fopen_s(&pFile, path.c_str(), "r");
#else
				pFile = fopen(path.c_str(), "r");
#endif

				if (pFile != nullptr)
				{
					std::fread(&size, sizeof(size_t), 1, pFile);

					if (size == vecColliders.size())
					{
						for (size_t i = 0; i < vecColliders.size(); i++)
						{
							int32_t x = 0;
							int32_t y = 0;
							int32_t width = 0;
							int32_t height = 0;
							float rotation = 0.0f;

							std::fread(&x, sizeof(int32_t), 1, pFile);
							std::fread(&y, sizeof(int32_t), 1, pFile);
							std::fread(&width, sizeof(int32_t), 1, pFile);
							std::fread(&height, sizeof(int32_t), 1, pFile);
							std::fread(&rotation, sizeof(float), 1, pFile);

							vecColliders[i].SetPosition(x, y);
							vecColliders[i].SetWidth(width);
							vecColliders[i].SetHeight(height);
							vecColliders[i].SetRotation(rotation);

							//IF_COUT
							//{
							//	std::cout << "vec[" << i << "]: " << x << ", " << y << ", " << width << ", " << height << ", " << rotation << std::endl;
							//};
						}
					}

					fclose(pFile);
				}
			}

			IF_COUT{ std::cout << "load success" << std::endl; }
		}

		static void SaveColliderData(std::vector<BoxCollider>& vecColliders, std::string colliderFileName)
		{
			std::string path = "BoxColliderData/";

			if (colliderFileName.compare("none") != 0)
			{
				path += colliderFileName;

				FILE* pFile;
				size_t vecSize = vecColliders.size();

#ifdef _WIN32
				fopen_s(&pFile, path.c_str(), "w");
#else
				pFile = fopen(path.c_str(), "w");
#endif

				if (pFile != nullptr)
				{
					fwrite(&vecSize, sizeof(size_t), 1, pFile);

					IF_COUT{ std::cout << "saving collider data.." << std::endl; }

					for (size_t i = 0; i < vecColliders.size(); i++)
					{
						int32_t x = vecColliders[i].Position().x;
						int32_t y = vecColliders[i].Position().y;
						int32_t width = vecColliders[i].Width();
						int32_t height = vecColliders[i].Height();
						float rotation = vecColliders[i].Rotation();

						fwrite(&x, sizeof(int32_t), 1, pFile);
						fflush(pFile);
						fwrite(&y, sizeof(int32_t), 1, pFile);
						fflush(pFile);
						fwrite(&width, sizeof(int32_t), 1, pFile);
						fflush(pFile);
						fwrite(&height, sizeof(int32_t), 1, pFile);
						fflush(pFile);
						fwrite(&rotation, sizeof(float), 1, pFile);
						fflush(pFile);

						IF_COUT
						{
							std::cout << "vec[" << i << "]: " << x << ", " << y << ", " << width << ", " << height << ", " << rotation << std::endl;
						};
					}

					fclose(pFile);
				}
			}
		}
	};
}