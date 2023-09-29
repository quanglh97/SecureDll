#include "pch.h"
#include "attempt.h"
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

static unsigned long long previous_;  // Previous value, if any
static unsigned long long current_;   // Current sequence value
static unsigned index_;

using namespace std;

#include <Wincrypt.h>
#pragma comment (lib, "Advapi32.lib")
#pragma comment (lib, "Version.lib")

#define BUFSIZE 1024
#define MD5LEN  16


Attempt::Attempt(int x) {
	this->x = x;

}
int Attempt::adding(int y) {
	return this->x + y;
}

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
    string newPort = pasreIP(vStrings[1]);
    strcpy_s(buf, 200, (newIP + ":" + newPort).c_str());
    return;
}

const char* ChangeStr(string strPrx) {
    vector < string > vStrings = customSplit(strPrx, ':');
    string newIP = pasreIP(vStrings[0]);
    string newPort = pasrePort(vStrings[1]);
    string result = newIP + ":" + newPort;
    return  _strdup(result.c_str());
}

string urlEncode(string str) {
    string new_str = "";
    char c;
    int ic;
    const char* chars = str.c_str();
    char bufHex[10];
    int len = strlen(chars);

    for (int i = 0; i < len; i++) {
        c = chars[i];
        ic = c;
        // uncomment this if you want to encode spaces with +
        /*if (c==' ') new_str += '+';
        else */if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') new_str += c;
        else {
            sprintf_s(bufHex, "%X", c);
            if (ic < 16)
                new_str += "%0";
            else
                new_str += "%";
            new_str += bufHex;
        }
    }
    return new_str;
}

string urlDecode(string str) {
    string ret;
    char ch;
    int i, ii, len = str.length();

    for (i = 0; i < len; i++) {
        if (str[i] != '%') {
            if (str[i] == '+')
                ret += ' ';
            else
                ret += str[i];
        }
        else {
            sscanf_s(str.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        }
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

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

DWORD WINAPI myThread(LPVOID lpParameter)
{
    string trueMd5 = "GDCE4:C8HH8F5H:8DG3FD3F863H6E9H8";    //md5 cộng 2

    std::string sPpName = GetProcessName(GetPpid());
    std::transform(sPpName.begin(), sPpName.end(), sPpName.begin(),
        [](unsigned char c) { return std::tolower(c); });

    if (sPpName.find(DownLine("gzrnqtgt0gzg")) != std::string::npos) // explorer.exe
    {
        SetEnvironmentVariableA(delete_line("YkpfqyuZ:8").c_str(), gen_random(32).c_str()); //K6Tools_Check_Pass_FB
        //SetEnvironmentVariableA(delete_line("YkpfqyuZ:8").c_str(), "co van de"); //K6Tools_Check_Pass_FB
        Sleep(300000);
        raise(SIGSEGV);
        return 1;
    }

    CHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string sPath = buffer;
    sPath = std::string(buffer).substr(0, std::string(buffer).find_last_of("\\/"));
    sPath += DownLine("^EjgemRcuuHD0gzg");
    
    std::string sMD5 = has_md5(sPath);
    std::transform(sMD5.begin(), sMD5.end(), sMD5.begin(),
        [](unsigned char c) { return std::toupper(c); });

    std::string sFileVersion = GetVersionFile(sPath);
    //if (sFileVersion.find("2.1") != std::string::npos && sMD5.find(delete_line("477;G;4F:HCDGEFHE8;4E:F589D9C4C4")) != std::string::npos) // check là đúng version và trùng md5
    if (sMD5.find(DownLine(trueMd5)) != std::string::npos) // check là đúng version và trùng md5
    {
        SetEnvironmentVariableA(DownLine("YkpfqyuZ:8").c_str(), md5_Q8tools(sMD5).c_str());
    }

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