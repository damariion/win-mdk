#include "../../include/object/buffer.h"
using namespace mdk;

// argumentless
buffer::buffer(): buffer(1){}
// size-exclusive 
buffer::buffer(SIZE_T size): buffer(NULL, size){}
// entire (full)
buffer::buffer(HANDLE handle, SIZE_T size)
{
	if (!(this->file = mdk::nt().kernel32.call<HANDLE>("CreateFileMappingA",
		INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, NULL, (this->size = size), NULL)))
	{ throw std::exception(); }

	if (!(this->handle = mdk::nt().kernel32.call<HANDLE>("MapViewOfFile",
		this->file, FILE_MAP_WRITE | FILE_MAP_EXECUTE, NULL, NULL, this->size)))
	{ throw std::exception(); }
	

	if (!handle)
		RtlSecureZeroMemory(this->handle, this->size);
	else
	{
		RtlCopyMemory(this->handle, handle, this->size);
		RtlSecureZeroMemory(handle, this->size);
	}
}

buffer::~buffer()
{
	RtlSecureZeroMemory(this->handle, this->size);

	if (!mdk::nt().kernel32.call<BOOL>("CloseHandle", (this->file)))
		throw std::exception();
}

VOID buffer::execute()
{
	(*(VOID(*)()) this->handle)();
}

VOID buffer::encrypt(hash::hasher* hash)
{
	hash->apply(this->handle, this->size);
}