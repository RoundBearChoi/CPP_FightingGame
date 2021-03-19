#pragma once
#include "BodyType.h"

namespace RB
{
	class TargetBodyType
	{
	public:
		BodyType selectedType = BodyType::HEAD;

		void NextType()
		{
			int32_t next = (int32_t)selectedType + 1;

			if (next > (int32_t)BodyType::RIGHT_FOOT)
			{
				next = (int32_t)BodyType::HEAD;
			}

			selectedType = (BodyType)next;
		}

		void PrevType()
		{
			int32_t next = (int32_t)selectedType + 1;

			if (next < (int32_t)BodyType::HEAD)
			{
				next = (int32_t)BodyType::RIGHT_FOOT;
			}

			selectedType = (BodyType)next;
		}

		std::string GetCurrentSelString()
		{
			switch (selectedType)
			{
			case BodyType::HEAD: return "head";

			case BodyType::UPPERBODY: return "upper body";
			case BodyType::LOWERBODY: return "lower body";

			case BodyType::LEFT_ELBOW: return "left elbow";
			case BodyType::LEFT_FOREARM: return "left forearm";
			case BodyType::LEFT_HAND: return "left hand";
			
			case BodyType::RIGHT_ELBOW: return "right elbow";
			case BodyType::RIGHT_FOREARM: return "right forearm";
			case BodyType::RIGHT_HAND: return "right hand";

			case BodyType::LEFT_KNEE: return "left knee";
			case BodyType::LEFT_LOWERLEG: return "left lower leg";
			case BodyType::LEFT_FOOT: return "left foot";
			
			case BodyType::RIGHT_LOWERLEG: return "right lower leg";
			case BodyType::RIGHT_KNEE: return "right knee";
			case BodyType::RIGHT_FOOT: return "right foot";
			}

			return nullptr;
		}
	};
}