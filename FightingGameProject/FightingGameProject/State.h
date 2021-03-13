#pragma once
#include "ObjData.h"
#include "GameData.h"
#include "AnimationController.h"

namespace RB
{
	class State
	{
	protected:
		bool entered = false;

	public:
		State* nextState = nullptr;
		AnimationController animationController;

		virtual void OnEnter(ObjData& objData, GameData& gameData) = 0;
		virtual void UpdateState(ObjData& objData, GameData& gameData) = 0;

		void TriggerEnter(ObjData& objData, GameData& gameData)
		{
			if (!entered)
			{
				entered = true;
				OnEnter(objData, gameData);
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