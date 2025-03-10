#pragma once

#include "../core.h"
#include "hasher.h"

namespace mdk::hash
{
	class xor_: public hasher
	{
	public:

		INT64 key;
	
		xor_();
		xor_(INT64);
	
		virtual VOID apply(PVOID, SIZE_T) override;
		static INT64 keygen();
	};
}