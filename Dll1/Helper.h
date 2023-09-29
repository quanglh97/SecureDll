#include <wtypes.h>
#include <oleauto.h>
#include <string>
#include <vector>

#include <comutil.h> // #include for _bstr_t
#pragma comment (lib, "comsuppw.lib" ) // link with "comsuppw.lib" (or debug version: "comsuppwd.lib")

using namespace std;

string UpLine2(string sData);
string UpLine1(string sData);
string UpLine3(string sData);
vector < string > customSplit(string str, char separator);

extern "C" _declspec(dllexport) int GetDataWindowKernel(const char* tableName, const char* checkTable);

extern "C" _declspec(dllexport) BSTR SetDataWindowKernel(const char* tableName, const char* tableValue, const char * tableType)
{
    string strTableName = tableName;
    string strTableValue = tableValue;
    string strTableType = tableType;
    string result = strTableName + UpLine1("_ng-O6-rgkcXmlc=qKwIcw;") + strTableValue + UpLine1("$rwnc;").c_str() + strTableType;
    _bstr_t bstr = result.c_str();
    return SysAllocString(bstr);
    //return SysAllocString(L"String to return");
}

extern "C" _declspec(dllexport) BSTR SetDataWindowKernelX86(const char* tableName, const char* tableValue, const char* tableType)
{
    string strTableName = tableName;
    string strTableValue = tableValue;
    string strTableType = tableType;
    string result = strTableName + UpLine1("_ng-O6-T_jscV64=qKwIcw;") + strTableValue + UpLine1("$rwnc;").c_str() + strTableType;
    _bstr_t bstr = result.c_str();
    return SysAllocString(bstr);
}