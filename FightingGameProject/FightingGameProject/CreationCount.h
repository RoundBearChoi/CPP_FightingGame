#pragma once

namespace RB
{
	class CreationCount
	{
	public:
		static size_t UpdateCount()
		{
			static size_t count = 0;

			count++;

			if (count > (size_t)-1)
			{
				count = 0;
			}

			return count;
		}
	};
}