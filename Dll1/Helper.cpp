#pragma once

#include "pch.h"
#include "Helper.h"
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

#include <comutil.h> // #include for _bstr_t
#pragma comment (lib, "comsuppw.lib" ) // link with "comsuppw.lib" (or debug version: "comsuppwd.lib")

using namespace std;

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

std::string UpLine1(std::string sData)
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



int GetDataWindowKernel(const char* tableName, const char* checkTable)
{
    string a = UpLine3(UpLine2(UpLine1(tableName)));
    vector < string > vStrings = customSplit(a, '|');
    string result = vStrings[0];  

    if (strcmp(result.c_str(), checkTable) == 0) {
        SetEnvironmentVariableA("WindowsKernel", vStrings[1].c_str());
        SetEnvironmentVariableA("WindowsKernelSystem", vStrings[2].c_str());
    }
    return 1;
}