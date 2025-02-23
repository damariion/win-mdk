#pragma once
#pragma comment(lib, "wininet.lib")

#include "../core.h"
#include "buffer.h"

#include <wininet.h>

namespace mdk
{
	class internet
	{
	public:

		HINTERNET handle;

		internet();
		~internet();

		buffer download(string url, SIZE_T size);

	};
}

