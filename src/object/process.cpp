#include "../../include/object/process.h"
using namespace mdk;

process::process(string name): process(process::to_pid(name)) {}
process::process(DWORD id): pid(id)
{
	this->handle = mdk::nt().kernel32.call<HANDLE>
		("OpenProcess", PROCESS_ALL_ACCESS, FALSE, (this->pid));

	if (this->handle == NULL)
	{ throw std::exception(); }
}

VOID process::inject(buffer* data)
{
	LPVOID address = mdk::nt().kernel32.call<LPVOID>("VirtualAllocEx", this->handle,
		NULL, data->size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	SIZE_T bytes;
	mdk::nt().kernel32.call<VOID>("WriteProcessMemory",
		this->handle, address, data->handle, data->size, &bytes);

	mdk::nt().kernel32.call<VOID>("CreateRemoteThread", this->handle,
		NULL, data->size, (LPTHREAD_START_ROUTINE)address, NULL, NULL, NULL);
}

VOID process::inject(dll* data)
{
	LPCSTR name = data->name;
	buffer dllb = buffer(&name, data->size);
	this->inject(&dllb);
}

DWORD process::to_pid(string name)
{
	DWORD pid = 0;
	HANDLE snapshot = NULL;
	PROCESSENTRY32W process;

	if (!(snapshot = mdk::nt().kernel32.call<HANDLE>(
		"CreateToolhelp32Snapshot", TH32CS_SNAPPROCESS, 0))) goto eof;

	process.dwSize = sizeof(PROCESSENTRY32W);
	if (mdk::nt().kernel32.call<BOOL>("Process32FirstW",
		snapshot, &process) == FALSE) goto eof;

	do
	{
		std::wstring _ = std::wstring(process.szExeFile);
		string current = string(_.begin(), _.end());

		if (std::strcmp(name.c_str(), current.c_str()) == 0)
		{
			pid = process.th32ProcessID;
			goto eof;
		}

	} while (mdk::nt().kernel32.call<BOOL>("Process32NextW", snapshot, &process));

eof:
	return pid;
}

vector<thread> process::threads()
{
	HANDLE snapshot = NULL;
	vector<thread> threads;
	THREADENTRY32  _thread;

	if (!(snapshot = mdk::nt().kernel32.call<HANDLE>(
		"CreateToolhelp32Snapshot", TH32CS_SNAPTHREAD, 0))) goto eof;

	_thread.dwSize = sizeof(THREADENTRY32);
	if (mdk::nt().kernel32.call<BOOL>(
		"Thread32First", snapshot, &_thread) == FALSE) goto eof;

	threads = vector<thread>();
	do
	{
		if (_thread.th32OwnerProcessID == mdk::nt().kernel32.call<BOOL>(
			"GetProcessId", this->handle)) threads.push_back(thread(_thread.th32ThreadID));

	} while (mdk::nt().kernel32.call<BOOL>("Thread32Next", snapshot, &_thread));

eof:
	return threads;
}