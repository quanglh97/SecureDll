// TestFunction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "helper.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <exception>
#include <errno.h>
#include <stdlib.h>

#pragma unmanaged
//
//#ifdef _DEBUG
using namespace std;



std::string Cong2line(std::string sData) //build name environment 
{
	for (int i = 0; i < sData.length(); i++)
		if (sData[i] != '\0')
			sData[i] = sData[i] + 2;

	return sData;
}


std::string Tru2line(std::string sData) //build http     //build prx
{
	for (int i = 0; i < sData.length(); i++)
		if (sData[i] != '\0')
			sData[i] = sData[i] - 2;

	return sData;
}


std::string BuilDataline(std::string sData)
{
	for (int i = 0; i < sData.length(); i++)
		if (sData[i] != '\0')
			sData[i] = sData[i] - 6;

	return sData;
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

std::string AFunction(std::string sData) //build data key
{
	for (int i = 0; i < sData.length(); i++)
		if (sData[i] != '\0')
			sData[i] = sData[i] - 6;

	return sData;
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

int main()
{
	//try
	//{
	//	std::ifstream f("D:\\MMO\\CSharp\\ServerProduct\\SecureDll\\x64\\Debug\\proxy_k2_check_pass.txt");

	//	if (!f)
	//	{
	//		std::cerr << "ERROR: Cannot open 'teste.txt'!" << std::endl;
	//		exit(1);
	//	}
	//	std::string line;
	//	std::list<std::string> mylist;

	//	while (std::getline(f, line))
	//	{
	//		string test2 = urlEncode(line);
	//		test2 = Tru2line(test2);
	//		mylist.push_back(test2);
	//		std::cout << mylist.back() << std::endl;
	//	}
	//}
	//catch (const std::exception& ex)
	//{
	//	std::cerr << "Exception: '" << ex.what() << "'!" << std::endl;
	//	exit(1);
	//}




	//const char* strPrx = "192.168.3.4:1999";
	const char* test = "\\CheckPageFB.exe";  // check ip server
	string nameBuild = Cong2line(test);
	string nameBuilds = Tru2line("^EjgemRcuuHD0gzg");
	//const char* test3 = "WindowsX86";  // check MD5 file
	string trueMD5 = "0268F2F03AC9A6F26BDC0C831134ED86";
	string eviMD5 = md5_Q8tools(trueMD5);  // để check trong environment

	string dataNormal = eviMD5 + "|http://95.216.80.182:8080/|normal";  // check MD5 file  -6
	string dataVIP = eviMD5 + "|http://95.216.80.182:8080/|VIP";  // check MD5 file  -6
	string tempNormal = dataNormal;
	string tempVip = dataVIP;
	string test2 = AFunction(tempNormal);
	string test3 = AFunction(tempVip);

	string nameAPIPRx = "api/Q8/ValueX86?sMyKey="; //prx  
	string nameAPI = "api/Q8/timeZone?sMyKey="; 
	nameAPIPRx = Tru2line(nameAPIPRx);


	

}
