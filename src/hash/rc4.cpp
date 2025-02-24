#include "../../include/hash/rc4.h"
using namespace mdk::hash;

typedef struct
{
	DWORD	Length;
	DWORD	MaximumLength;
	PVOID	Buffer;

} USTRING;

rc4::rc4(): rc4(NULL, NULL) { }
rc4::rc4(PCHAR key, SIZE_T length): len(length)
{
	this->key = key;
	if (!key)
	{
		int size  = rand() % (12 - 6 + 1) + 6;
		this->len = size;
		
		this->key = (PCHAR) malloc(this->len);
		this->keygen(this->key, this->len);
	}
}

VOID rc4::keygen(PCHAR key, SIZE_T len)
{
	for (INT i = 0; i < len; i++)
	{
		key[i] = rand() % (0x126 - 33 + 1) + 33;
	}
}

VOID rc4::apply(PVOID data, SIZE_T size)
{

	USTRING udata;
	udata.Buffer = data;
	udata.Length = size;
	udata.MaximumLength = size;

	USTRING ukey;
	ukey.Buffer = this->key;
	ukey.Length = this->len;
	ukey.MaximumLength = this->len;

	mdk::nt().advapi32.call<NTSTATUS>(
		"SystemFunction033", &udata, &ukey);
	data = udata.Buffer;

}