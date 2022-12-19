// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include <string>
#include <iostream>
#include <algorithm>
#include <wtclap/CmdLine.h>

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    // Wrap everything in a try block.  Do this every time,
    // because exceptions will be thrown for problems.
    try {
        // Define the command line object.
        CmdLine cmd(L"Command description message", L'=', L"0.9");

        SwitchArg atmcSwitch(L"a", L"atmc", L"aContinuous time semantics", false);
        SwitchArg btmcSwitch(L"b", L"btmc", L"bDiscrete time semantics", false);
        cmd.xorAdd(atmcSwitch, btmcSwitch);

        // Parse the args.
        cmd.parse(argc, argv);

    } catch (ArgException &e)  // catch any exceptions
    {
        wcerr << L"error: " << e.error() << L" for arg " << e.argId() << endl;
    }
}
