// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include <string>
#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    // Wrap everything in a try block.  Do this every time,
    // because exceptions will be thrown for problems.
    try {
        // Define the command line object.
        CmdLine cmd(L"Command description message", L' ', L"0.9");

        vector<wstring> allowed;
        allowed.push_back(L"homer");
        allowed.push_back(L"marge");
        allowed.push_back(L"bart");
        allowed.push_back(L"lisa");
        allowed.push_back(L"maggie");
        ValuesConstraint<wstring> allowedVals(allowed);

        ValueArg<wstring> nameArg(L"n", L"name", L"Name to print", true, L"homer",
                                 &allowedVals);
        cmd.add(nameArg);

        vector<int> iallowed;
        iallowed.push_back(1);
        iallowed.push_back(2);
        iallowed.push_back(3);
        ValuesConstraint<int> iallowedVals(iallowed);

        UnlabeledValueArg<int> intArg(L"times", L"Number of times to print", true,
                                      1, &iallowedVals, false);
        cmd.add(intArg);

        // Parse the args.
        cmd.parse(argc, argv);

        // Get the value parsed by each arg.
        int num = intArg.getValue();
        wstring name = nameArg.getValue();

        for (int i = 0; i < num; i++) wcout << L"My name is " << name << endl;

    } catch (ArgException &e)  // catch any exceptions
    {
        wcerr << L"error: " << e.error() << L" for arg " << e.argId() << endl;
    }
}
