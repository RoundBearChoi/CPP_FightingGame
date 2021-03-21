#pragma once
#include <iostream>
#include "DevSettings.h"
#include "ObjData.h"
#include "GameData.h"
#include "AnimationController.h"

namespace RB
{
	class State
	{
	protected:
		bool isNew = true;
		std::string path = "none";

		void MakeHash(size_t& _hash)
		{
			if (_hash == 0)
			{
				IF_COUT{ std::cout << "hashing: " << path << std::endl; }
				_hash = std::hash<std::string>{}(path);
				IF_COUT{ std::cout << _hash << std::endl; };
			}
		}

	public:
		State* nextState = nullptr;
		AnimationController animationController;

		virtual size_t GetHash() = 0;
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