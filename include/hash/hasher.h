#pragma once
#include "../core.h"

#include <random>

namespace mdk::hash
{
	class hasher
	{
	public:
	
		CHAR  key;
		SIZE_T len;
	
		virtual VOID apply(PVOID, SIZE_T) = 0;
	
	};
}