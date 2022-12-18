// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include <string>
#include <iostream>
#include <algorithm>
#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    try {
        CmdLine cmd(L"Command description message", L' ', L"0.9", true);

        cmd.setExceptionHandling(false);

        cmd.parse(argc, argv);

    } catch (ArgException &e) {  // catch any exceptions
        wcerr << L"error: " << e.error() << L" for arg " << e.argId() << endl;
        return 1;
    } catch (ExitException &e) {  // catch any exceptions
        wcerr << L"Exiting on ExitException." << endl;
        return e.getExitStatus();
    }
}
