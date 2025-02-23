#pragma once
#include "../core.h"

#include "thread.h"
#include "buffer.h"

#include <tlhelp32.h>

namespace mdk
{
	class process
	{
	public:

		HANDLE handle;
		DWORD  pid;

		process(DWORD);
		process(string);

		VOID inject(buffer*);
		VOID inject(dll*);

		vector<thread> threads();

	private:

		DWORD to_pid(string);

	};
}
