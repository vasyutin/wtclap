// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include <iostream>
#include <string>

#include <wtclap/CmdLine.h>

using namespace TCLAP;

//
// This file tests that we can parse args from a vector
// of strings rather than argv.  This also tests a bug
// where a single element in the vector contains both
// the flag and value AND the value contains the flag
// from another switch arg.  This would fool the parser
// into thinking that the string was a combined switches
// string rather than a flag value combo.
//
// This should not print an error
//
// Contributed by Nico Lugil.
//
int main() {
    try {
        CmdLine cmd(L"Test", L' ', L"not versioned", true);

        MultiArg<std::wstring> Arg(L"X", L"fli", L"fli module", false, L"string");
        cmd.add(Arg);
        MultiSwitchArg ArgMultiSwitch(L"d", L"long_d", L"example");
        cmd.add(ArgMultiSwitch);

        std::vector<std::wstring> in;
        in.push_back(L"prog name");
        in.push_back(L"-X module");
        cmd.parse(in);

        std::vector<std::wstring> s = Arg.getValue();
        for (unsigned int i = 0; i < s.size(); i++) {
            std::wcout << s[i] << L"\n";
        }
        std::wcout << L"MultiSwtichArg was found " << ArgMultiSwitch.getValue()
                  << L" times.\n";

    } catch (ArgException &e)  // catch any exceptions
    {
        std::wcerr << L"error: " << e.error() << L" for arg " << e.argId()
                  << std::endl;
    }

    std::wcout << L"done...\n";

    return 0;
}
