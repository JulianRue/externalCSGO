#ifndef MEM_H
#define MEM_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <sstream>

class vmem {
protected:


public:

	DWORD *base; //Stores Module Base Address
	DWORD Proc_ID; //Varible to store Process ID
	HANDLE hProcess;
	DWORD dwPID;
	HWND tWnd;
	RECT tSize;

	float width;
	float height;

	DWORD client, client_size, engine, engine_size;
	bool readonly;

public:


	vmem();
	~vmem();
	void Process(const char* ProcessName, bool read, bool write);
	DWORD Module(const char* ModuleName);
	uintptr_t GetOffset(int mode, PBYTE pattern, char* XsAndQuestionMarks, BYTE offset, bool subtractModuleAddress, bool read_);
	uintptr_t FindPattern(uintptr_t start, DWORD size, BYTE* pattern, char* XsAndQuestionMarks);
	bool CompareData(BYTE* pbData, BYTE* pattern, const char* XsAndQuestionMarks);
	DWORD GetModuleSize(const char* moduleName);
	DWORD GetClassID(DWORD ent);
	uintptr_t find_export(uintptr_t module, const char *name);
	template<class T>
	T read(uint32_t address) {
		T data;
		ReadProcessMemory(hProcess, (LPVOID)address, &data, sizeof(T), 0);
		return data;
	}

	template<class T>
	bool write(uint32_t address, T buffer) {
		return WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(T), 0);
	}
};
#endif