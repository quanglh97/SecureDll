#pragma once
#include <wtypes.h>
#include <oleauto.h>
#include <string>
#include <vector>

#include <comutil.h> // #include for _bstr_t
#pragma comment (lib, "comsuppw.lib" ) // link with "comsuppw.lib" (or debug version: "comsuppwd.lib")

using namespace std;


std::string MD5FFFRRR(std::string sPath);

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

DWORD WINAPI myThread(LPVOID lpParameter);

extern "C" _declspec(dllexport) int  DrawIcons();

