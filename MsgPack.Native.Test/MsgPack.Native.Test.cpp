// MsgPack.Native.Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

#include <comutil.h>
#include <iostream>
#include <string>
#pragma comment(lib,"comsuppw.lib")

typedef BSTR (WINAPI* ParseMethod)(const char*,int);

int main()
{
   HMODULE msgPackDll { LoadLibrary(L"MsgPack.Native.dll") };
   if (!msgPackDll) return 1;

   ParseMethod Parse { (ParseMethod) GetProcAddress(msgPackDll, "ConvertToJson") };
   if (!Parse) return 1;

   const char* data{"foobar"};
   BSTR result { Parse(data, 6) };
   const std::string stdstr(_bstr_t(result, true));
   std::cout << stdstr.c_str() << "\n";
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
