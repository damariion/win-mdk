#pragma once
#include "../core.h"

#include <cmath>
#include <random>

namespace mdk::hash
{
	class hasher
	{
	public:
	
		virtual VOID apply(PVOID, SIZE_T) = 0;
	
	};
}