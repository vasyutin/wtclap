// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

// This illustrates how to change the flag and name start strings.
// Note that these defines need to happen *before* tclap is included!
#define TCLAP_NAMESTARTSTRING L"~~"
#define TCLAP_FLAGSTARTSTRING L"/"

#include <string>
#include <iostream>
#include <algorithm>
#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    // Wrap everything in a try block.  Do this every time,
    // because exceptions will be thrown for problems.
    try {
        // Define the command line object.
        CmdLine cmd(L"Command description message", L' ', L"0.9");

        // Define a value argument and add it to the command line.
        ValueArg<wstring> nameArg(L"n", L"name", L"Name to print", true, L"homer",
                                 L"string");
        cmd.add(nameArg);

        // Define a switch and add it to the command line.
        SwitchArg reverseSwitch(L"r", L"reverse", L"Print name backwards", false);
        cmd.add(reverseSwitch);

        // Parse the args.
        cmd.parse(argc, argv);

        // Get the value parsed by each arg.
        wstring name = nameArg.getValue();
        bool reverseName = reverseSwitch.getValue();

        // Do what you intend too...
        if (reverseName) {
            reverse(name.begin(), name.end());
            wcout << L"My name (spelled backwards) is: " << name << endl;
        } else
            wcout << L"My name is: " << name << endl;

    } catch (ArgException &e)  // catch any exceptions
    {
        wcerr << L"error: " << e.error() << L" for arg " << e.argId() << endl;
    }
}
