#include "../../include/object/internet.h"
using namespace mdk;

internet::internet()
{
	
	if (!(this->handle = mdk::nt().wininet.call<HINTERNET>
		("InternetOpenW", NULL, NULL, NULL, NULL, NULL)))
	{
		throw std::exception();
	}
}

internet::~internet()
{
	mdk::nt().wininet.call<LPVOID>(
		"InternetCloseHandle", this->handle);
}

buffer internet::download(string url, SIZE_T size)
{
	DWORD bytes; // trash in most cases

	HINTERNET handle = mdk::nt().wininet.call<HINTERNET>(
		"InternetOpenUrlA", this->handle, url.c_str(), NULL, NULL, 
		INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID, NULL);

	if (!handle) throw std::exception();

	auto buffer = mdk::buffer(size);
	mdk::nt().wininet.call<BOOL>("InternetReadFile", 
		handle,buffer.handle, buffer.size, &bytes);

	mdk::nt().wininet.call<LPVOID>("InternetCloseHandle", handle);
	return buffer;
}