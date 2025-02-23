#pragma once
#include "../core.h"

#include "../hash/hasher.h"

namespace mdk
{
	class buffer
	{
	public:

		HANDLE handle;
		HANDLE file;
		SIZE_T size;
	
		buffer();
		~buffer();
	
		buffer(SIZE_T);
		buffer(HANDLE, SIZE_T);
	
		VOID execute();
		VOID encrypt(hash::hasher*);
	};
}