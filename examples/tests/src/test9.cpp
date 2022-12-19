// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include <string>
#include <iostream>
#include <algorithm>
#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    try {
        CmdLine cmd(L"Command description message", L' ', L"0.9", false);

        SwitchArg reverseSwitch(L"r", L"reverse", L"REVERSE instead of FORWARDS",
                                false);
        cmd.add(reverseSwitch);

        MultiSwitchArg verbose(L"V", L"verbose", L"Level of verbosity");
        cmd.add(verbose);

        MultiSwitchArg noise(L"N", L"noise", L"Level of noise", 5);
        cmd.add(noise);

        UnlabeledValueArg<wstring> word(L"word", L"a random word", false, L"string",
                                       L"won't see this", false);
        cmd.add(word);

        // Uncommenting the next arg will (correctly) cause an exception
        // to be thrown.

        //	UnlabeledMultiArg<wstring> badword(L"badword","a bad word",
        //false,"string");
        //
        //	cmd.add( badword );

        cmd.parse(argc, argv);

        bool reverseName = reverseSwitch.getValue();

        if (reverseName)
            wcout << L"REVERSE" << endl;
        else
            wcout << L"FORWARD" << endl;

        if (verbose.isSet())
            wcout << L"Verbose level: " << verbose.getValue() << endl;

        if (noise.isSet()) wcout << L"Noise level: " << noise.getValue() << endl;

        if (word.isSet()) wcout << L"Word: " << word.getValue() << endl;

    } catch (ArgException &e)  // catch any exceptions
    {
        wcerr << L"error: " << e.error() << L" for arg " << e.argId() << endl;
    }
}
