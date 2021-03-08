#pragma once

namespace RB
{
	class ObjGroup
	{
	private:
		size_t creationCount = 0;

	protected:
		size_t GetCreationCount()
		{
			creationCount++;

			if (creationCount > (size_t)-1)
			{
				creationCount = 0;
			}

			return creationCount;
		}

	public:
		virtual void RenderObjPosition() = 0;
	};
}