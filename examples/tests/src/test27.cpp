#include "wtclap/CmdLine.h"
#include <iostream>
#include <string>

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    CmdLine cmd(L"test arg conversion operator");
    SwitchArg falseSwitch(L"f", L"false", L"test false condition", cmd, false);
    SwitchArg trueSwitch(L"t", L"true", L"tests true condition", cmd, true);
    ValueArg<wstring> strArg(L"s", L"str", L"test string arg", false, L"defStr",
                            L"string", cmd);
    ValueArg<int> intArg(L"i", L"int", L"tests int arg", false, 4711, L"integer",
                         cmd);

    cmd.parse(argc, argv);

    wstring s = strArg;
    int i = intArg;

    wcout << L"for falseSwitch we got : " << falseSwitch << endl
         << L"for trueSwitch we got : " << trueSwitch << endl
         << L"for strArg we got : " << s << endl
         << L"for intArg we got : " << i << endl;
}
