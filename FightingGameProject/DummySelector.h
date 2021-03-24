#pragma once

#include "GameObj.h"

#include "Fighter_0_Idle.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_WalkForward.h"
#include "Fighter_0_WalkBack.h"

namespace RB
{
	class DummySelector
	{
	private:
		std::array<GameObj*, 4> arrObjs;
		size_t currentIndex = 0;

	public:
		DummySelector()
		{
			for (size_t i = 0; i < arrObjs.size(); i++)
			{
				arrObjs[i] = new GameObj;
			}

			Init<Fighter_0_Idle>(*arrObjs[0]);
			Init<Fighter_0_Jab>(*arrObjs[1]);
			Init<Fighter_0_WalkForward>(*arrObjs[2]);
			Init<Fighter_0_WalkBack>(*arrObjs[3]);
		}

		~DummySelector()
		{
			for (size_t i = 0; i < arrObjs.size(); i++)
			{
				delete arrObjs[i];
			}
		}

		GameObj* Current()
		{
			return arrObjs[currentIndex];
		}

		GameObj* Next()
		{
			currentIndex++;

			if (currentIndex > arrObjs.size())
			{
				currentIndex = 0;
			}

			return arrObjs[currentIndex];
		}

		GameObj* Prev()
		{
			currentIndex--;

			if (currentIndex < 0)
			{
				currentIndex = arrObjs.size() - 1;
			}

			return arrObjs[currentIndex];
		}

		template<class T>
		void Init(GameObj& obj)
		{
			obj.stateController.CreateNewState<T>();
			obj.objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
		}
	};
}