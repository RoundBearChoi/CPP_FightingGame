#pragma once
#include "ObjData.h"
#include "GameData.h"
#include "AnimationController.h"

namespace RB
{
	class State
	{
	protected:
		bool isNew = true;

	public:
		State* nextState = nullptr;
		AnimationController animationController;

		virtual void OnEnter(ObjData& objData, GameData& gameData) = 0;
		virtual void UpdateState(ObjData& objData, GameData& gameData) = 0;

		bool IsNew()
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

		template<class T>
		static State* NewState()
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