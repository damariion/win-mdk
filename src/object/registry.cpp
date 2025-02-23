#include "../../include/object/registry.h"
using namespace mdk;

registry::registry(HKEY key, LPCSTR sub)
{
	
	if (mdk::nt().advapi32.call<LSTATUS>("RegOpenKeyExA", key,
		sub, 0, KEY_ALL_ACCESS, &this->handle) != ERROR_SUCCESS)
	{ throw std::exception(); }
}

registry::~registry()
{
	if (!mdk::nt().kernel32.call<HANDLE>
		("CloseHandle", this->handle))
	{ throw std::exception(); }
}

VOID registry::set(LPCSTR sub, mdk::buffer* data)
{
	if (mdk::nt().advapi32.call<LSTATUS>("RegSetValueExA",this->handle, 
		sub, NULL, REG_BINARY, (const BYTE*)data->handle, data->size) != ERROR_SUCCESS)
	{ throw std::exception(); }
}

buffer registry::get(LPCSTR sub, LPCSTR value)
{
	DWORD size = NULL;
	if (RegGetValueA(this->handle, sub, value, 
		RRF_RT_ANY, NULL, NULL, &size) != ERROR_SUCCESS)
	{ throw std::exception(); }

	auto buf = buffer(size);
	if (RegGetValueA(this->handle,sub, value, 
		RRF_RT_ANY, NULL, buf.handle, &size) != ERROR_SUCCESS)
	{ throw std::exception(); }

	return buf;
}