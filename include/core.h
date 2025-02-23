#pragma once

#include <Windows.h>
#include <exception>

#include <string>
#include <format>
#include <vector>

using std::string;
using std::format;
using std::vector;

namespace mdk
{
	class dll
	{

	public:

		HANDLE handle;
		LPCSTR name;
		SIZE_T size;

		dll(string library): name(library.c_str()), size(strlen(library.c_str()))
		{
			if ((this->handle = GetModuleHandleA(this->name)) == NULL)
				LoadLibraryA(this->name);
			else
				return;

			if ((this->handle = GetModuleHandleA(this->name)) == NULL)
				throw std::exception("invalid library (DLL) name provided");
		}

		FARPROC find(string function)
		{
			if (this->handle == NULL)
				return NULL;

			auto dll = (PBYTE)handle;

			auto dos = (PIMAGE_DOS_HEADER)dll;
			auto nte = (PIMAGE_NT_HEADERS)(dll + dos->e_lfanew);
			auto opt = (IMAGE_OPTIONAL_HEADER)(nte->OptionalHeader);
			auto exp = (PIMAGE_EXPORT_DIRECTORY)(dll + opt.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

			auto names = (PDWORD)(dll + exp->AddressOfNames);
			auto funcs = (PDWORD)(dll + exp->AddressOfFunctions);
			auto cords = (PWORD)(dll + exp->AddressOfNameOrdinals);

			for (INT i = 0; i < exp->NumberOfFunctions; i++)
			{
				if (strcmp(function.c_str(), (PCHAR)(dll + names[i])) == 0)
				{
					return (FARPROC) (dll + funcs[cords[i]]);
				}
			}
		}

		template <typename T, typename... A>
		T call(string function, A... args)
		{
			// re-attempts
			INT failures = 5;

			try
			{
				return (*(T(*)(A...)) this->find(function))(args...);
			}
			catch (...)
			{
				if (failures-- <= 0) 
					throw std::exception("Couldn't access library function");
			}
		}
	};

	static class nt
	{

	public:

		mdk::dll kernel32 = mdk::dll("Kernel32.dll");
		mdk::dll advapi32 = mdk::dll("Advapi32.dll");
		mdk::dll wininet = mdk::dll("Wininet.dll");

	};
}