#include "../../include/hash/xor.h"
using namespace mdk::hash;

xor_::xor_(): xor_::xor_(NULL) {};
xor_::xor_(CHAR key)
{
	this->key = key;
	if (!key) this->key = this->keygen();
}

CHAR xor_::keygen()
{
	srand(time(0));
	return rand() % 256;
}

VOID xor_::apply(PVOID data, SIZE_T size)
{
	CHAR* cursor = (CHAR*)data;
	for (INT i = 0; i < size; i++)
	{
		cursor[i] ^= this->key;
	}
}