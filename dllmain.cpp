// dllmain.cpp : Определяет точку входа для приложения DLL.

#include "Header.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{

    HANDLE mut;
    mut = CreateMutex(NULL, FALSE, "MyStartDll");
    DWORD result;
    result = WaitForSingleObject(mut, 0);
    if (result == WAIT_OBJECT_0)
    {
        myLog("!!!!!!!! Take mutex");
        start();
        ReleaseMutex(mut);
    }
    myLog("!!!!!!!! Not take mutex");
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

