#pragma once

namespace RB
{
	class JumpAdder
	{
	private:
		std::vector<GameObj*>* _vecObjs = nullptr;

	public:
		JumpAdder(std::vector<GameObj*>* vecObjs)
		{
			_vecObjs = vecObjs;
		}

		void AddJump(int32_t index, int32_t upForce, int32_t sideForce)
		{
			std::vector<GameObj*>& vec = *_vecObjs;

			vec[index]->objData.CreateJumpProcessor();
			vec[index]->objData.ptrJumpProcessor->allowControl = false;
			vec[index]->objData.ptrJumpProcessor->moveBack = true;
			vec[index]->objData.ptrJumpProcessor->moveHorizontally = true;
			vec[index]->objData.ptrJumpProcessor->minimumSideForce = 1;

			vec[index]->objData.ptrJumpProcessor->SetUpForce(upForce);
			vec[index]->objData.ptrJumpProcessor->SetSideForce(sideForce);
		}
	};
}