#pragma once

#include "../core.h"
#include "hasher.h"

namespace mdk::hash
{
	class xor_: public hasher
	{
	public:
	
		xor_();
		xor_(CHAR key);
	
		virtual VOID apply(PVOID, SIZE_T) override;
		static CHAR keygen();
	};
}