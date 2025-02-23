#include "../../include/object/thread.h"
using namespace mdk;

thread::thread(DWORD id): tid(id)
{
	this->handle = mdk::nt().kernel32.call<HANDLE>(
		"OpenThread", THREAD_ALL_ACCESS, FALSE, this->tid);

	if (this->handle == NULL)
		throw std::exception();
	
}