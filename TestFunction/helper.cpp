#pragma once

#include <vector>
#include <string>
#include <wtypes.h>
#include < atlconv.h >

#include <iostream>
#include <string>
#include <iomanip>

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
#include <atlconv.h>

#include <wtypes.h>
#include <oleauto.h>
#include <string>
#include <vector>

#include "helper.h"

#include <comutil.h> // #include for _bstr_t
#pragma comment (lib, "comsuppw.lib" ) // link with "comsuppw.lib" (or debug version: "comsuppwd.lib")


#include <comutil.h> // #include for _bstr_t
#pragma comment (lib, "comsuppw.lib" ) // link with "comsuppw.lib" (or debug version: "comsuppwd.lib")

using namespace std;

#define BUFSIZE 1024
#define MD5LEN  16

//DWORD GetPpid()
//{
//    HANDLE hSnapshot;
//    PROCESSENTRY32 pe32;
//    DWORD ppid = 0, pid = GetCurrentProcessId();
//
//    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//    __try {
//        if (hSnapshot == INVALID_HANDLE_VALUE) __leave;
//
//        ZeroMemory(&pe32, sizeof(pe32));
//        pe32.dwSize = sizeof(pe32);
//        if (!Process32First(hSnapshot, &pe32)) __leave;
//
//        do {
//            if (pe32.th32ProcessID == pid) {
//                ppid = pe32.th32ParentProcessID;
//                break;
//            }
//        } while (Process32Next(hSnapshot, &pe32));
//
//    }
//    __finally {
//        if (hSnapshot != INVALID_HANDLE_VALUE) CloseHandle(hSnapshot);
//    }
//    return ppid;
//}
//
//std::string GetProcessName(DWORD pid)
//{
//
//    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
//
//    if (hProcess == NULL)
//    {
//        return "";
//    }
//
//    char szBuffer[MAX_PATH] = { 0 };
//    if (GetProcessImageFileNameA(hProcess, szBuffer, MAX_PATH) == 0)
//    {
//        CloseHandle(hProcess);
//        return "";
//    }
//
//    if (hProcess != NULL)
//    {
//        CloseHandle(hProcess);
//    }
//
//    return szBuffer;
//}

//std::string GetVersionFile(std::string sPath)
//{
//    DWORD  verHandle = 0;
//    UINT   size = 0;
//    LPBYTE lpBuffer = NULL;
//    CHAR szBuff[20] = { 0 };
//    DWORD  verSize = GetFileVersionInfoSizeA(sPath.c_str(), &verHandle);
//
//    if (verSize != NULL)
//    {
//        LPSTR verData = new char[verSize];
//
//        if (GetFileVersionInfoA(sPath.c_str(), verHandle, verSize, verData))
//        {
//            if (VerQueryValueA(verData, "\\", (VOID FAR * FAR*) & lpBuffer, &size))
//            {
//                if (size)
//                {
//                    VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
//                    if (verInfo->dwSignature == 0xfeef04bd)
//                    {
//                        sprintf_s(szBuff, "%d.%d",
//                            (verInfo->dwFileVersionMS >> 16) & 0xffff,
//                            (verInfo->dwFileVersionMS >> 0) & 0xffff);
//                    }
//                }
//            }
//        }
//
//        delete[] verData;
//    }
//
//    return szBuff;
//}



// Create custom split() function.  
vector < string > customSplit(string str, char separator) {
    int startIndex = 0, endIndex = 0;
    vector < string > vStrings;

    for (int i = 0; i <= str.size(); i++) {

        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            vStrings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }

    return vStrings;
}

string pasreIP(string strIP) {
    vector < string > vStrings = customSplit(strIP, '.');
    vector < int > vInts;
    vInts.push_back(stoi(vStrings[0]) - 2);
    vInts.push_back(stoi(vStrings[1]) - 2);
    vInts.push_back(stoi(vStrings[2]) - 2);
    vInts.push_back(stoi(vStrings[3]) - 6);

    string newIP = to_string(vInts[0]) + "." + to_string(vInts[1]) + "." + to_string(vInts[2]) + "." + to_string(vInts[3]);
    return newIP;
}

string pasrePort(string strPort) {
    return to_string(stoi(strPort) - 6000);
}

void ChangeStr(const char* strPrx, char* buf) {
    string temp = strPrx;
    vector < string > vStrings = customSplit(temp, ':');
    string newIP = pasreIP(vStrings[0]);
    string newPort = pasrePort(vStrings[1]);
    strcpy_s(buf, 200, (newIP + ":" + newPort).c_str());
    return;
}



/// <summary>
/// //////////////////////////////////////////////////////////
/// </summary>
/// <param name="sData"></param>
/// <returns></returns>

std::string UpLine1(std::string sData)  //build name check md5
{
    for (int i = 0; i < sData.length(); i++)
        if (sData[i] != '\0')
            sData[i] = sData[i] + 2;

    return sData;
}

std::string UpLine2(std::string sData)
{
    for (int i = 0; i < sData.length(); i++)
        if (sData[i] != '\0')
            sData[i] = sData[i] + 1;

    return sData;
}

std::string UpLine3(std::string sData)
{
    for (int i = 0; i < sData.length(); i++)
        if (sData[i] != '\0')
            sData[i] = sData[i] + 3;

    return sData;
}

std::string md5_q8tools(std::string sMD5)
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

bool GetDataWindowKernel(const char* tableName, const char* checkTable)
{
    string a = UpLine3(UpLine2(UpLine1(tableName)));
    vector < string > vStrings = customSplit(a, '|');
    string result = vStrings[0];

    if (strcmp(result.c_str(), checkTable) == 0) {
        SetEnvironmentVariableA("WindowsKernel", vStrings[1].c_str());
    }

    return true;
    //return SysAllocString(L"String to return");
}