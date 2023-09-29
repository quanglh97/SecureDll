// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include"Source.h"
#pragma unmanaged

#ifdef _DEBUG

int main()
{
    DrawIcons();
    int a = 0;
    a++;
    Sleep(50000);
    return 0;
}

#else
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
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
#endif

