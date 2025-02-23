#pragma once
#include "../core.h"

namespace mdk
{
	class thread
	{
	public:

		HANDLE handle;
		DWORD tid;

		thread(DWORD);
	};
}

