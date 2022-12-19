// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-
//
// Test that xor args can't be required

#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    try {
        CmdLine cmd(L"this is a message", L' ', L"0.99");

        ValueArg<wstring> atest(L"a", L"aaa", L"or test a", true, L"homer",
                               L"string");
        ValueArg<wstring> btest(L"b", L"bbb", L"or test b", false, L"homer",
                               L"string");
        cmd.xorAdd(atest, btest);

        cmd.parse(argc, argv);
    } catch (SpecificationException &e) {
        std::wcout << L"Caught SpecificationException: " << e.what() << std::endl;
        return 0;
    }

    return 1;
}
