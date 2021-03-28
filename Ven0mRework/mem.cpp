#include "mem.h"

using namespace std;

vmem::vmem() {
	
}

vmem::~vmem() {
	CloseHandle(hProcess);
}

DWORD vmem::GetClassID(DWORD ent) {
	int vt = read<int>(ent + 0x8);	// Vtable
	int fn = read<int>(vt + 2 * 0x4);	// Function
	int cls = read<int>(fn + 0x1);	// Class
	int clsn = read<int>(cls + 8);	// Class Name
	return read<int>(cls + 20);	// ClassID
	
}


void vmem::Process(const char* ProcessName, bool read, bool write) {

	HWND hWcs = FindWindow(NULL, "Counter-Strike: Global Offensive");
	GetWindowThreadProcessId(hWcs, &Proc_ID);

	tWnd = hWcs;
	GetWindowRect(tWnd, &tSize);

	width = (int)(tSize.right - tSize.left);
	height = (int)(tSize.bottom - tSize.top);

	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(ProcEntry);


	do
		if (!strcmp(ProcEntry.szExeFile, ProcessName))
		{


			dwPID = ProcEntry.th32ProcessID;
			CloseHandle(hPID);

			if (read && write) {
				readonly = false;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
			}
			else if (read) {
				readonly = true;
				hProcess = OpenProcess(PROCESS_VM_READ, FALSE, dwPID);
			}
			return;
		}
	while (Process32Next(hPID, &ProcEntry));

	cout << "\nCould not find the process csgo.exe...\n\n";
	system("pause");
	exit(0);
}

DWORD vmem::Module(const char* ModuleName) {


	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);


	do
		if (!strcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
	while (Module32Next(hModule, &mEntry));

	cout << "\nClient.dll not found. Try again\n\n";
	return 0;
}

bool vmem::CompareData(BYTE* pbData, BYTE* pattern, const char* XsAndQuestionMarks) {
	for (; *XsAndQuestionMarks; ++XsAndQuestionMarks, ++pbData, ++pattern)
	{
		if (*XsAndQuestionMarks == 'x' && *pbData != *pattern)
		{
			return FALSE;
		}
	}
	return (*XsAndQuestionMarks) == NULL;
}

uintptr_t vmem::FindPattern(uintptr_t start, DWORD size, BYTE* pattern, char* XsAndQuestionMarks) {
	unsigned long bytesRead;
	BYTE* data = new BYTE[size];

	if (!ReadProcessMemory(hProcess, (LPVOID)start, data, size, &bytesRead))
	{
		delete data;
		return NULL;
	}

	for (DWORD i = 0; i < size; i++)
	{
		if (CompareData((BYTE*)(data + i), (BYTE*)pattern, XsAndQuestionMarks))
		{
			delete data;
			return start + i;
		}
	}
	delete data;
	return NULL;
}
/*
uintptr_t vmem::GetOffset(uintptr_t BaseAddress, size_t ModuleSize, const char *Signature, const char *SignatureMask)
{
	if (!BaseAddress)
		return 0;

	//So we know when to stop searching.
	BOOL Found = FALSE;
	//Index to step through each of the module's addresses.
	int Step = 0;
	//The number of bytes to scan.
	int SignatureSize = strlen(SignatureMask);

	//The bytes we are going to read.
	BYTE *BytesRead = (BYTE *)calloc(SignatureSize + 1, sizeof(BYTE));

	//Start scanning.
	do {
		//The current address.We start from here and scan 'SignatureSize' number of bytes.
		uintptr_t CurrentAddress = BaseAddress + Step;

		//Read the current address and save the first 'SignatureSize' number of bytes.
		if (ReadProcessMemory(hProcess, (BYTE*)CurrentAddress, BytesRead, SignatureSize, NULL))
		{
			//We assume we have found the address.
			Found = TRUE;
			//We step through each read byte.
			for (int i = 0; i < SignatureSize; i++)
				//If the mask indicates that there is a valid byte, we then compare each read byte with the ones from our signature.
				//This statement is negated.
				if (SignatureMask[i] == 'x' && (BYTE)Signature[i] != BytesRead[i])
				{
					//The read bytes didn't match our signature so we stop comparing.
					Found = FALSE;
					break;
				}
		}

		//We go to the next address.
		Step++;
	} while (Found == FALSE && Step < ModuleSize);

	//If our signature matches the read bytes, we assume we have found the offset and return it.
	//This method of parsing the bytes is easily customizable.
	if (Found)
	{
		//Temporary buffer used for conversion.
		char TempBuffer[17] = "";	//17 = Two octets + 1 (to support 64bit addresses)

		//We step through our read bytes once more in order to extract our offset.
		for (int i = SignatureSize - 1; i >= 0; i--)
			//We extract the offset.
			if (SignatureMask[i] == '?')
			{
				//We convert each byte to a char array.
				char CurrentByte[3] = "";
				//Convert byte to hex
				sprintf(CurrentByte, "%.2X", (uintptr_t)(BytesRead[i]));

				//We concatenate each converted byte to our temporary buffer.
				strcat(TempBuffer, CurrentByte);
			}
		//We free our memory.
		free(BytesRead);

		//We convert our temporary char array to an unsigned int and return it.
		return (uintptr_t)(strtoul(TempBuffer, NULL, 16));
	}

	//We have failed to find the offset.

	//We free our memory.
	free(BytesRead);
	return 0;
}
*/

//GetOffset(uintptr_t BaseAddress, size_t ModuleSize, const char *Signature, const char *SignatureMask)
uintptr_t vmem::GetOffset(int mode, PBYTE pattern, char* XsAndQuestionMarks, BYTE offset, bool subtractModuleAddress, bool read_) {
	DWORD base1 = mode == 0 ? client : engine;
	DWORD size1 = mode == 0 ? client_size : engine_size;	

	uintptr_t patternAddress = FindPattern(base1, size1, pattern, XsAndQuestionMarks);

	uintptr_t dwOffset = patternAddress + offset;

	if (read_) {
		dwOffset = read<uintptr_t>(dwOffset);
	}

	if (!subtractModuleAddress)
		return dwOffset;
	else
		return dwOffset - base1;
}


DWORD vmem::GetModuleSize(const char* moduleName) {
	HANDLE hSnap;
	MODULEENTRY32 xModule;

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	xModule.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnap, &xModule)) {
		while (Module32Next(hSnap, &xModule)) {
			if (!strncmp((char*)xModule.szModule, moduleName, 8)) {
				CloseHandle(hSnap);
				return (DWORD)xModule.modBaseSize;
			}
		}
	}

	CloseHandle(hSnap);

	return 0;
}

