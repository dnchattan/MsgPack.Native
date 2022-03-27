// MsgPack.Native.Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

#include <comutil.h>
#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <fstream>
#pragma comment(lib,"comsuppw.lib")

typedef BSTR(WINAPI* ParseMethod)(const char*, int);
typedef HRESULT(WINAPI* ConvertToJsonBuf)(const char*, int, const char*, size_t*);

#define BUFFER_SIZE (1024 * 1024 * 5)

int main()
{
	HMODULE msgPackDll { LoadLibrary(L"MsgPack.Native.dll") };
	if (!msgPackDll) return 1;

	const std::string inputFile = "ByteBufferRaw";
	std::ifstream infile(inputFile, std::ios_base::binary);
	std::vector<char> buffer { std::istreambuf_iterator<char>(infile),
		std::istreambuf_iterator<char>() };

#ifdef _DEBUG
	{
		std::cout << "ConvertToJson_DEBUG" << "\n";
		ParseMethod Parse { (ParseMethod) GetProcAddress(msgPackDll, "ConvertToJson_DEBUG") };
		BSTR result { Parse(buffer.data(), buffer.size()) };
		const std::string stdstr(_bstr_t(result, true));
		std::cout << stdstr.substr(0, 500).c_str() << "\n";
	}
#endif
	{
		std::cout << "ConvertToJson" << "\n";
		ParseMethod Parse { (ParseMethod) GetProcAddress(msgPackDll, "ConvertToJson") };
		BSTR result { Parse(buffer.data(), buffer.size()) };
		const std::string stdstr(_bstr_t(result, true));
		std::cout << stdstr.substr(0, 500).c_str() << "\n";
	}
	{
		std::cout << "ConvertToJsonBuf" << "\n";
		char* buf { nullptr };
		size_t cBuf { 0 };
		ConvertToJsonBuf Parse { (ConvertToJsonBuf) GetProcAddress(msgPackDll, "ConvertToJsonBuf") };
		HRESULT result { Parse(buffer.data(), buffer.size(), buf, &cBuf) };
		std::cout << "HRESULT(0): " << result << "\n";
		buf = reinterpret_cast<char*>(malloc(cBuf));
		memset(buf, 0, cBuf);
		result = Parse(buffer.data(), buffer.size(), buf, &cBuf);
		std::cout << "HRESULT(1): " << result << "\n";
		const std::string stdstr{ buf, cBuf };
		std::cout << stdstr.substr(0,500).c_str() << "\n";
		free(buf);
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
