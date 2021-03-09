#pragma once
#include "ObjData.h"
#include "GameData.h"

namespace RB
{
	class State
	{
	public:
		State* nextState = nullptr;

		virtual void OnEnter(ObjData& objData, GameData& gameData) = 0;
		virtual void UpdateState(ObjData& objData, GameData& gameData) = 0;

		template<class T>
		static State* CreateState()
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
	};
}