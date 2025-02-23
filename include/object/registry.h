#pragma once

#include "../core.h"
#include "buffer.h"

namespace mdk
{
	class registry
	{
	public:

		HKEY handle;

		registry(HKEY, LPCSTR);
		~registry();

		VOID set(LPCSTR, buffer*);
		buffer get(LPCSTR sub, LPCSTR value);

	};
}