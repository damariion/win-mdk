#include "../../include/hash/xor.h"
using namespace mdk::hash;

xor_::xor_(): xor_::xor_(NULL) {};
xor_::xor_(INT64 key)
{
	this->key = key;
	if (!key) 
		this->key = this->keygen();
}

INT64 xor_::keygen()
{
	srand(time(0));
	int   min = 1.0e8;
	INT64 max = INT16_MAX;

	return rand() % (max - min + 1) + min;
}

VOID xor_::apply(PVOID data, SIZE_T size)
{
	CHAR* cursor = (CHAR*)data;
	for (INT i = 0; i < size; i++)
	{
		cursor[i] ^= this->key;
	}
}