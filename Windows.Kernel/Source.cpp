#include "Source.h"
// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include <vector>
#include <string>
#include <ostream>
#include <winver.h>
#include <signal.h>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <Windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>

// DLL internal state variables:
static unsigned long long previous_;  // Previous value, if any
static unsigned long long current_;   // Current sequence value
static unsigned index_;

#define CURL_STATICLIB

#include <Wincrypt.h>
#pragma comment (lib, "Advapi32.lib")
#pragma comment (lib, "Version.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Wldap32.lib")

// include debug 64
#if defined(_DEBUG) && defined(_WIN64)
#pragma comment (lib, "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/lib/libcurl_a_debug.lib")
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/curl.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/curlver.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/easy.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/header.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/mprintf.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/multi.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/options.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/stdcheaders.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/system.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/urlapi.h"
#include "lib/x64_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/websockets.h"
#endif

// include release 64
#if !defined(_DEBUG) && defined(_WIN64)
#pragma comment (lib, "lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/lib/libcurl_a.lib")
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/curl.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/curlver.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/easy.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/header.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/mprintf.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/multi.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/options.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/stdcheaders.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/system.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/urlapi.h"
#include "../Windows.Kernel/lib/x64_Release/libcurl-vc17-x64-release-static-ipv6-sspi-schannel/include/curl/websockets.h"
#endif


// include debug 32
#if defined(_DEBUG) && !defined(_WIN64)
#pragma comment (lib, "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/lib/libcurl_a_debug.lib")
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/curl.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/curlver.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/easy.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/header.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/mprintf.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/multi.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/options.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/stdcheaders.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/system.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/urlapi.h"
#include "lib/x32_Debug/libcurl-vc17-x64-debug-static-ipv6-sspi-schannel/include/curl/websockets.h"
#endif


// include release 32
#if !defined(_DEBUG) && !defined(_WIN64)
#pragma comment (lib, "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/lib/libcurl_a.lib")
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/curl.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/curlver.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/easy.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/header.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/mprintf.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/multi.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/options.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/stdcheaders.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/system.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/urlapi.h"
#include "lib/x32_Release/libcurl-vc17-x86-release-static-ipv6-sspi-schannel/include/curl/websockets.h"
#endif
#include <filesystem>
#include <fstream>


#define BUFSIZE 1024
#define MD5LEN  16

DWORD GetPpid()
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0, pid = GetCurrentProcessId();

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    __try {
        if (hSnapshot == INVALID_HANDLE_VALUE) __leave;

        ZeroMemory(&pe32, sizeof(pe32));
        pe32.dwSize = sizeof(pe32);
        if (!Process32First(hSnapshot, &pe32)) __leave;

        do {
            if (pe32.th32ProcessID == pid) {
                ppid = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));

    }
    __finally {
        if (hSnapshot != INVALID_HANDLE_VALUE) CloseHandle(hSnapshot);
    }
    return ppid;
}

std::string GetProcessName(DWORD pid)
{

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);

    if (hProcess == NULL)
    {
        return "";
    }

    char szBuffer[MAX_PATH] = { 0 };
    if (GetProcessImageFileNameA(hProcess, szBuffer, MAX_PATH) == 0)
    {
        CloseHandle(hProcess);
        return "";
    }

    if (hProcess != NULL)
    {
        CloseHandle(hProcess);
    }

    return szBuffer;
}

std::string GetVersionFile(std::string sPath)
{
    DWORD  verHandle = 0;
    UINT   size = 0;
    LPBYTE lpBuffer = NULL;
    CHAR szBuff[20] = { 0 };
    DWORD  verSize = GetFileVersionInfoSizeA(sPath.c_str(), &verHandle);

    if (verSize != NULL)
    {
        LPSTR verData = new char[verSize];

        if (GetFileVersionInfoA(sPath.c_str(), verHandle, verSize, verData))
        {
            if (VerQueryValueA(verData, "\\", (VOID FAR * FAR*) & lpBuffer, &size))
            {
                if (size)
                {
                    VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd)
                    {
                        sprintf_s(szBuff, "%d.%d",
                            (verInfo->dwFileVersionMS >> 16) & 0xffff,
                            (verInfo->dwFileVersionMS >> 0) & 0xffff);
                    }
                }
            }
        }

        delete[] verData;
    }

    return szBuff;
}

std::string md5_Q8tools(std::string sMD5)
{
    sMD5.at(0) = 'Q';
    sMD5.at(4) = '8';
    sMD5.at(8) = 'T';
    sMD5.at(12) = 'O';
    sMD5.at(16) = 'O';
    sMD5.at(20) = 'L';
    sMD5.at(24) = 'S';

    return sMD5;
}

std::string has_md5(std::string sPath)
{
    DWORD dwStatus = 0;
    BOOL bResult = FALSE;
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HANDLE hFile = NULL;
    BYTE rgbFile[BUFSIZE];
    DWORD cbRead = 0;
    BYTE rgbHash[MD5LEN];
    DWORD cbHash = 0;
    CHAR rgbDigits[] = "0123456789abcdef";
    std::string sOutput = "";

    // Logic to check usage goes here.

    hFile = CreateFileA(sPath.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL);

    if (INVALID_HANDLE_VALUE == hFile)
    {
        dwStatus = GetLastError();
        sOutput = "\n Error opening file " + sPath + " error code : " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
        return "";
    }

    // Get handle to the crypto provider
    if (!CryptAcquireContext(&hProv,
        NULL,
        NULL,
        PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT))
    {
        dwStatus = GetLastError();
        CloseHandle(hFile);
        sOutput = "\n CryptAcquireContext failed: eror code " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
        return "";
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
    {
        dwStatus = GetLastError();
        CloseHandle(hFile);
        CryptReleaseContext(hProv, 0);
        sOutput = "\n CryptCreateHash failed: eror code " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
        return "";
    }

    while (bResult = ReadFile(hFile, rgbFile, BUFSIZE,
        &cbRead, NULL))
    {
        if (0 == cbRead)
        {
            break;
        }

        if (!CryptHashData(hHash, rgbFile, cbRead, 0))
        {
            dwStatus = GetLastError();
            CryptReleaseContext(hProv, 0);
            CryptDestroyHash(hHash);
            CloseHandle(hFile);
            sOutput = "\n CryptHashData failed: eror code " + std::to_string(dwStatus);
            OutputDebugStringA(sOutput.c_str());
            return "";
        }
    }

    if (!bResult)
    {
        dwStatus = GetLastError();
        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CloseHandle(hFile);
        sOutput = "\n ReadFile failed: eror code " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
        return "";
    }

    cbHash = MD5LEN;
    std::string sMD5 = "";
    CHAR szBuff[20] = { 0 };
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
    {
        for (DWORD i = 0; i < cbHash; i++)
        {
            sprintf_s(szBuff, "%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
            sMD5 += szBuff;
            memset(szBuff, 0, 20);
        }
    }
    else
    {
        dwStatus = GetLastError();
        sOutput = "\n CryptGetHashParam failed: eror code " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);

    if (sMD5 == "")
    {
        sOutput = "\n Canot get md5 file " + sPath;
        OutputDebugStringA(sOutput.c_str());
    }
    else
    {
        sOutput = "\n Get md5 file success " + sPath + " md5 = " + sMD5;
        OutputDebugStringA(sOutput.c_str());
    }

    return sMD5;
}

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

std::string delete_line(std::string sData)
{
    for (int i = 0; (i < 100 && sData[i] != '\0'); i++)
        sData[i] = sData[i] - 2;

    return sData;
}

std::string DownLine(std::string sData)
{
    for (int i = 0; i < sData.length(); i++)
        if (sData[i] != '\0')
            sData[i] = sData[i] - 2;

    return sData;
}

std::string UpLine1(std::string sData)
{
    for (int i = 0; i < sData.length(); i++)
        if (sData[i] != '\0')
            sData[i] = sData[i] + 2;

    return sData;
}

bool ABHIDAHNAID(std::string& sSource)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    std::string sOutput = "";

    std::string sDest = "";
    std::string directory = std::filesystem::path(sSource).parent_path().u8string();
    if (directory == "" || directory.empty())
    {
#ifdef _WRITELOG_:
        sOutput = "Canoot find folder current";
        OutputDebugStringA(sOutput.c_str());
#endif
        return false;
    }
    sDest = directory + "\\XCheckPassFB.exe";
    std::string sCMD = "C:\\Windows\\system32\\xcopy.exe /f /y \"" + sSource + "\" \"" + sDest + "*\"";

    // Start the child process. 
    if (!CreateProcessA(NULL,   // No module name (use command line)
        (char*)sCMD.c_str(),        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NO_WINDOW,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
#ifdef _WRITELOG_:
        sOutput = "CreateProcess false cmd : " + sCMD;
        OutputDebugStringA(sOutput.c_str());
#endif
        return false;
    }

#ifdef _WRITELOG_:
    sOutput = "CreateProcess success cmd : " + sCMD;
    OutputDebugStringA(sOutput.c_str());
#endif


    // Wait until child process exits.
    DWORD dwExitCode = WaitForSingleObject(pi.hProcess, 10000);

    if (GetExitCodeProcess(pi.hProcess, &dwExitCode) == 0)
    {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
#ifdef _WRITELOG_:
        sOutput = "GetExitCodeProcess error code : " + std::to_string(GetLastError());
        OutputDebugStringA(sOutput.c_str());
#endif
        TerminateProcess(pi.hProcess, 1);

        return false;
    }

    //-- the task has ended so close the handle

    if (dwExitCode == 0)
    {
#ifdef _WRITELOG_:
        sOutput = "Process terminate success : " + std::to_string(GetLastError());
        OutputDebugStringA(sOutput.c_str());
#endif

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        TerminateProcess(pi.hProcess, 1);
        sSource = sDest;
        return true;
    }

#ifdef _WRITELOG_:
    sOutput = "GetExitCodeProcess out wait : " + std::to_string(dwExitCode);
    OutputDebugStringA(sOutput.c_str());
#endif

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    TerminateProcess(pi.hProcess, 1);

    return false;
}

std::string MD5FFFRRR(std::string sPath)
{
    DWORD dwStatus = 0;
    BOOL bResult = FALSE;
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HANDLE hFile = NULL;
    BYTE rgbFile[BUFSIZE];
    DWORD cbRead = 0;
    BYTE rgbHash[MD5LEN];
    DWORD cbHash = 0;
    CHAR rgbDigits[] = "0123456789abcdef";
    std::string sOutput = "";

    // Logic to check usage goes here.

    std::size_t found = sPath.rfind(".dll");
    if (found == std::string::npos)
    {
        if (!ABHIDAHNAID(sPath))
        {
            return "";
        }
    }

    hFile = CreateFileA(sPath.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL);

    if (INVALID_HANDLE_VALUE == hFile)
    {
        dwStatus = GetLastError();
#ifdef _WRITELOG_:
        sOutput = "\n Error opening file " + sPath + " error code : " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
#endif
        return "";
    }

    // Get handle to the crypto provider
    if (!CryptAcquireContext(&hProv,
        NULL,
        NULL,
        PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT))
    {
        dwStatus = GetLastError();
        CloseHandle(hFile);
#ifdef _WRITELOG_:
        sOutput = "\n CryptAcquireContext failed: eror code " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
#endif
        return "";
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
    {
        dwStatus = GetLastError();
        CloseHandle(hFile);
        CryptReleaseContext(hProv, 0);
#ifdef _WRITELOG_:
        sOutput = "\n CryptCreateHash failed: eror code " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
#endif
        return "";
    }

    while (bResult = ReadFile(hFile, rgbFile, BUFSIZE,
        &cbRead, NULL))
    {
        if (0 == cbRead)
        {
            break;
        }

        if (!CryptHashData(hHash, rgbFile, cbRead, 0))
        {
            dwStatus = GetLastError();
            CryptReleaseContext(hProv, 0);
            CryptDestroyHash(hHash);
            CloseHandle(hFile);
#ifdef _WRITELOG_:
            sOutput = "\n CryptHashData failed: eror code " + std::to_string(dwStatus);
            OutputDebugStringA(sOutput.c_str());
#endif
            return "";
        }
    }

    if (!bResult)
    {
        dwStatus = GetLastError();
        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CloseHandle(hFile);
#ifdef _WRITELOG_:
        sOutput = "\n ReadFile failed: eror code " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
#endif
        return "";
    }

    cbHash = MD5LEN;
    std::string sMD5 = "";
    CHAR szBuff[20] = { 0 };
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
    {
        for (DWORD i = 0; i < cbHash; i++)
        {
            sprintf_s(szBuff, "%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
            sMD5 += szBuff;
            memset(szBuff, 0, 20);
        }
    }
    else
    {
        dwStatus = GetLastError();
#ifdef _WRITELOG_:
        sOutput = "\n CryptGetHashParam failed: eror code " + std::to_string(dwStatus);
        OutputDebugStringA(sOutput.c_str());
#endif
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);

    if (sMD5 == "")
    {
#ifdef _WRITELOG_:
        sOutput = "\n Canot get md5 file " + sPath;
        OutputDebugStringA(sOutput.c_str());
#endif
    }

    return sMD5;
}


DWORD WINAPI myThread(LPVOID lpParameter)
{
    //std::string sPpName = GetProcessName(GetPpid());
    //std::transform(sPpName.begin(), sPpName.end(), sPpName.begin(),
    //    [](unsigned char c) { return std::tolower(c); });

    //if (sPpName.find(DownLine("gzrnqtgt0gzg")) == std::string::npos) // explorer.exe
    //{
    //    SetEnvironmentVariableA(delete_line("YkpfqyuZ:8").c_str(), gen_random(32).c_str()); //K6Tools_Check_Pass_FB
    //    //SetEnvironmentVariableA(delete_line("YkpfqyuZ:8").c_str(), "co van de"); //K6Tools_Check_Pass_FB
    //    Sleep(3000);
    //    raise(SIGSEGV);MD5FFFRRR
    //    return 1;
    //}
   
    //OutputDebugStringA("myThread 1");

    CHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string sPath = buffer;
    sPath = std::string(buffer).substr(0, std::string(buffer).find_last_of("\\/"));
    sPath += DownLine("^EjgemRcuuHD0gzg"); // tool check pass
    //sPath += DownLine("^EjgemRcigHD0gzg"); // tool check page

    //OutputDebugStringA("myThread 2");

    std::string sMD5 = MD5FFFRRR(sPath);
    std::transform(sMD5.begin(), sMD5.end(), sMD5.begin(),
        [](unsigned char c) { return std::toupper(c); });

    //OutputDebugStringA("myThread 3");

    std::string sFileVersion = GetVersionFile(sPath);

    //if (sFileVersion.find("2.1") != std::string::npos && sMD5.find(delete_line("477;G;4F:HCDGEFHE8;4E:F589D9C4C4")) != std::string::npos) // check là đúng version và trùng md5
    if (sMD5.length() >10) // check là đúng version và trùng md5
    {
        SetEnvironmentVariableA(DownLine("YkpfqyuZ:8").c_str(), md5_Q8tools(sMD5).c_str()); //WindowsX86
    }

   // OutputDebugStringA("myThread 4");

    return 1;
}

int __stdcall DrawIcons()
{
    using namespace std;

    unsigned int myCounter = 0;
    DWORD myThreadID;
    HANDLE myHandle = CreateThread(0, 0, myThread, &myCounter, 0, &myThreadID);

    CloseHandle(myHandle);
    return 0;
}

int draw_icon_exe()
{
    using namespace std;

    unsigned int myCounter = 0;
    DWORD myThreadID;
    HANDLE myHandle = CreateThread(0, 0, myThread, &myCounter, 0, &myThreadID);

    CloseHandle(myHandle);
    return 0;
}

// Produce the next value in the sequence.
// Returns true on success, false on overflow.
bool fibonacci_next()
{
    // check to see if we'd overflow result or position
    if ((ULLONG_MAX - previous_ < current_) ||
        (UINT_MAX == index_))
    {
        return false;
    }

    // Special case when index == 0, just return b value
    if (index_ > 0)
    {
        // otherwise, calculate next sequence value
        previous_ += current_;
    }
    std::swap(current_, previous_);
    ++index_;
    return true;
}

// Get the current value in the sequence.
unsigned long long fibonacci_current()
{
    return current_;
}

// Get the current index position in the sequence.
unsigned fibonacci_index()
{
    return index_;
}