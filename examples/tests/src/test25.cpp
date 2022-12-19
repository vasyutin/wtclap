// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include "wtclap/CmdLine.h"
#include "wtclap/DocBookOutput.h"
#include <iostream>
#include <string>

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    CmdLine cmd(L"this is a message", L' ', L"0.99");
    DocBookOutput docoutput;
    cmd.setOutput(&docoutput);

    SwitchArg btest(L"B", L"sB", L"exist Test B", false);
    MultiArg<int> atest(L"A", L"sA", L"exist Test A", false, L"integer");

    ValueArg<wstring> stest(L"s", L"Bs", L"string test", false, L"homer", L"string");

    cmd.xorAdd(stest, btest);
    cmd.add(atest);

    cmd.parse(argc, argv);
}
