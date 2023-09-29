// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#pragma unmanaged

//#ifdef _DEBUG
//int main()
//{
//    const char *strPrx = "192.168.3.4:1999";
//    char* buf = new char[1000];
//    ChangeStr(strPrx, buf);
//    printf_s("%s", buf);
//    int a = 0;
//    a++;
//    return 0;
//}
//#else

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

//#endif // DEBUG