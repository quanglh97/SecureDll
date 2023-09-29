
#include <string>
#include <vector>
#include <wtypes.h>
using namespace std;
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

vector < string > customSplit(string str, char separator);
string pasreIP(string strIP);
string pasrePort(string strPort);

/*EXTERN_DLL_EXPORT void ChangeStr(const char* strPrx, char* buf);*/
void ChangeStr(const char* strPrx, char* buf);
BSTR getDataFromTable(const char* tableName);

vector < string > customSplit(string str, char separator);

std::string UpLine2(std::string sData);
std::string UpLine1(std::string sData);
std::string UpLine3(std::string sData);

std::string BuilDataline(std::string sData);
std::string Cong2line(std::string sData);
std::string Tru2line(std::string sData);

 bool GetDataWindowKernel(const char* tableName, const char* checkTable);