#pragma once
#include "../core.h"
#include "hasher.h"

namespace mdk::hash
{
	class rc4: public hasher
	{
	public:

		PCHAR  key;
		SIZE_T len;

		rc4();
		rc4(PCHAR, SIZE_T);

		virtual VOID apply(PVOID, SIZE_T) override;
		static VOID keygen(PCHAR, SIZE_T);
	};
}