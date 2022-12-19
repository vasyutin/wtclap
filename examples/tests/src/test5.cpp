// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include "wtclap/CmdLine.h"
#include <iostream>
#include <string>

using namespace TCLAP;
using namespace std;

wstring _orTest;
wstring _orTest2;
wstring _testc;
bool _testd;

void parseOptions(int argc, wchar_t **argv);

int wmain(int argc, wchar_t **argv) {
    parseOptions(argc, argv);

    wcout << L"for A OR B we got : " << _orTest << endl
         << L"for string C we got : " << _testc << endl
         << L"for string D we got : " << _testd << endl
         << L"for E or F or G we got: " << _orTest2 << endl;
}

void parseOptions(int argc, wchar_t **argv) {
    try {
        CmdLine cmd(L"this is a message", L' ', L"0.99");

        //
        // Define arguments
        //

        ValueArg<wstring> atest(L"a", L"aaa", L"or test a", false, L"homer",
                               L"string");
        ValueArg<wstring> btest(L"b", L"bbb", L"or test b", false, L"homer",
                               L"string");
        cmd.xorAdd(atest, btest);

        ValueArg<wstring> ctest(L"c", L"ccc", L"c test", true, L"homer", L"string");
        cmd.add(ctest);

        SwitchArg dtest(L"", L"ddd", L"d test", false);
        cmd.add(dtest);

        ValueArg<wstring> etest(L"", L"eee", L"e test", false, L"homer", L"string");
        ValueArg<wstring> ftest(L"", L"fff", L"f test", false, L"homer", L"string");
        ValueArg<wstring> gtest(L"g", L"ggg", L"g test", false, L"homer", L"string");
        vector<Arg *> xorlist;
        xorlist.push_back(&etest);
        xorlist.push_back(&ftest);
        xorlist.push_back(&gtest);
        cmd.xorAdd(xorlist);

        MultiArg<wstring> itest(L"i", L"iii", L"or test i", false, L"string");
        MultiArg<wstring> jtest(L"j", L"jjj", L"or test j", false, L"string");
        cmd.xorAdd(itest, jtest);

        //
        // Parse the command line.
        //
        cmd.parse(argc, argv);

        //
        // Set variables
        //

        if (atest.isSet())
            _orTest = atest.getValue();
        else if (btest.isSet())
            _orTest = btest.getValue();
        else
            // Should never get here because TCLAP will note that one of the
            // required args above has not been set.
            throw(L"very bad things...");

        _testc = ctest.getValue();
        _testd = dtest.getValue();

        if (etest.isSet())
            _orTest2 = etest.getValue();
        else if (ftest.isSet())
            _orTest2 = ftest.getValue();
        else if (gtest.isSet())
            _orTest2 = gtest.getValue();
        else
            throw(L"still bad");

        if (jtest.isSet()) {
            wcout << L"for J:" << endl;
            vector<wstring> v = jtest.getValue();
            for (int z = 0; static_cast<unsigned int>(z) < v.size(); z++)
                wcout << L" " << z << L"  " << v[z] << endl;
        } else if (itest.isSet()) {
            wcout << L"for I:" << endl;
            vector<wstring> v = itest.getValue();
            for (int z = 0; static_cast<unsigned int>(z) < v.size(); z++)
                wcout << L" " << z << L"  " << v[z] << endl;
        } else
            throw(L"yup, still bad");

    } catch (ArgException &e) {
        wcout << L"ERROR: " << e.error() << L" " << e.argId() << endl;
    }
}
