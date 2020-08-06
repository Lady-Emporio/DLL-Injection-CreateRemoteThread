
#include <Windows.h>
#include <strsafe.h>
#include <iostream>

//#define DLL_NAME "C:\\Users\\Иванова\\source\\repos\\Dll1\\Debug\\Dll1.dll"
#define DLL_NAME "C:/Users/Иванова/source/repos/HookWithDll/x64/Release/HookWithDll.dll"

BOOL InjectRemoteThread(DWORD ProcessID)
{
    HANDLE RemoteProc;
    char buf[50] = { 0 };
    LPVOID MemAlloc;
    LPVOID LoadLibAddress;

    // Process ID does show correctly!
    WCHAR id[100];
    StringCbPrintf(id, 100, L"%d", ProcessID); // id contains the process ID... is confirmed in comparing ID shown in tasklist and the messagebox.
    //MessageBox(NULL, id, L"Process ID", MB_ICONINFORMATION);
    // Process ID does show correctly!

    if (!ProcessID)
    {
        MessageBox(NULL, (LPCWSTR)GetLastError(), L"An error occured", NULL);
        return 0;
    }
    RemoteProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessID);
    if (!RemoteProc)
    {
        MessageBox(NULL, (LPCWSTR)GetLastError(), L"An error occured", NULL);
        return 0;
    }
    LoadLibAddress = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    MemAlloc = (LPVOID)VirtualAllocEx(RemoteProc, NULL, strlen(DLL_NAME) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(RemoteProc, (LPVOID)MemAlloc, DLL_NAME, strlen(DLL_NAME) + 1, NULL);
    CreateRemoteThread(RemoteProc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddress, (LPVOID)MemAlloc, NULL, NULL);

    CloseHandle(RemoteProc);
    VirtualFreeEx(RemoteProc, (LPVOID)MemAlloc, 0, MEM_RELEASE | MEM_DECOMMIT);
    return 1;
}

/*
void t1() {

    const char* buffer = "C:\\Users\\Иванова\\source\\repos\\Dll1\\x64\\Release\\Dll1.dll";

    int procID = 4272;
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    if (process == NULL) {
        printf("Error: the specified process couldn't be found.\n");
    }


    LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
    if (addr == NULL) {
        printf("Error: the LoadLibraryA function was not found inside kernel32.dll library.\n");
    }


    LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(buffer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (arg == NULL) {
        printf("Error: the memory could not be allocated inside the chosen process.\n");
    }


    int n = WriteProcessMemory(process, arg, buffer, strlen(buffer), NULL);
    if (n == 0) {
        printf("Error: there was no bytes written to the process's address space.\n");
    }


    HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)addr, arg, NULL, NULL);
    if (threadID == NULL) {
        printf("Error: the remote thread could not be created.\n");
    }
    else {
        printf("Success: the remote thread was successfully created.\n");
    }

    CloseHandle(process);
}

*/
int main()
{
    const char* buffer = "C:\\Users\\Иванова\\source\\repos\\Dll2\\x64\\Release\\Dll2.dll";

    int procID = 9300;
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    if (process == NULL) {
        printf("Error: the specified process couldn't be found.\n");
    }


    LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
    if (addr == NULL) {
        printf("Error: the LoadLibraryA function was not found inside kernel32.dll library.\n");
    }


    LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(buffer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (arg == NULL) {
        printf("Error: the memory could not be allocated inside the chosen process.\n");
    }


    int n = WriteProcessMemory(process, arg, buffer, strlen(buffer), NULL);
    if (n == 0) {
        printf("Error: there was no bytes written to the process's address space.\n");
    }


    HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)addr, arg, NULL, NULL);
    if (threadID == NULL) {
        printf("Error: the remote thread could not be created.\n");
    }
    else {
        printf("Success: the remote thread was successfully created.\n");
    }

    CloseHandle(process);

}