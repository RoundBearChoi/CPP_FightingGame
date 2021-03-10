#pragma once

namespace RB
{
	class DecalPath
	{
	public:
		virtual int GetCount() = 0;
		virtual std::string GetPath(int _index) = 0;
	};
}