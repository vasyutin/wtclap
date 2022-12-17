// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include "wtclap/CmdLine.h"
#include <iostream>
#include <string>

using namespace TCLAP;
using namespace std;

// This exemplifies how the output class can be overridden to provide
// user defined output.
class MyOutput : public StdOutput {
public:
    virtual void failure(CmdLineInterface &c, ArgException &e) {
        static_cast<void>(c);  // Ignore input, don't warn
        wcerr << L"my failure message: " << endl << e.what() << endl;
        exit(1);
    }

    virtual void usage(CmdLineInterface &c) {
        wcout << L"my usage message:" << endl;
        list<Arg *> args = c.getArgList();
        for (ArgListIterator it = args.begin(); it != args.end(); it++)
            wcout << (*it)->longID() << "  (" << (*it)->getDescription() << ")"
                 << endl;
    }

    virtual void version(CmdLineInterface &c) {
        static_cast<void>(c);  // Ignore input, don't warn
        wcout << L"my version message: 0.1" << endl;
    }
};

bool _boolTestB;
bool _boolTestA;
wstring _stringTest;

void parseOptions(int argc, wchar_t **argv);

int wmain(int argc, wchar_t **argv) {
    parseOptions(argc, argv);

    wcout << L"for string we got : " << _stringTest << endl
         << L"for bool B we got : " << _boolTestB << endl
         << L"for bool A we got : " << _boolTestA << endl;
}

void parseOptions(int argc, wchar_t **argv) {
    try {
        CmdLine cmd(L"this is a message", L' ', L"0.99");

        // set the output
        MyOutput my;
        cmd.setOutput(&my);

        //
        // Define arguments
        //

        SwitchArg btest(L"B", L"sB", L"exist Test B", false);
        SwitchArg atest(L"A", L"sA", L"exist Test A", false);

        ValueArg<wstring> stest(L"s", L"Bs", L"string test", true, L"homer",
                               L"string");
        cmd.add(stest);
        cmd.add(btest);
        cmd.add(atest);

        //
        // Parse the command line.
        //
        cmd.parse(argc, argv);

        //
        // Set variables
        //
        _stringTest = stest.getValue();
        _boolTestB = btest.getValue();
        _boolTestA = atest.getValue();

    } catch (ArgException &e) {
        wcout << L"ERROR: " << e.error() << " " << e.argId() << endl;
    }
}
