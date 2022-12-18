// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#define TCLAP_SETBASE_ZERO 1

#include "wtclap/CmdLine.h"
#include <iostream>
#include <string>

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    try {
        CmdLine cmd(L"this is a message", L' ', L"0.99");

        ValueArg<int> itest(L"i", L"intTest", L"integer test", true, 5, L"int");
        cmd.add(itest);

        //
        // Parse the command line.
        //
        cmd.parse(argc, argv);

        //
        // Set variables
        //
        int _intTest = itest.getValue();
        wcout << L"found int: " << _intTest << endl;

    } catch (ArgException &e) {
        wcout << L"ERROR: " << e.error() << " " << e.argId() << endl;
    }
}
