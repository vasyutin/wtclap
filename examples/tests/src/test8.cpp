// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include "wtclap/CmdLine.h"
#include <iostream>
#include <string>

using namespace TCLAP;
using namespace std;

bool _boolTestB;
wstring _stringTest;
wstring _utest;
wstring _ztest;

void parseOptions(int argc, wchar_t **argv);

int wmain(int argc, wchar_t **argv) {
    parseOptions(argc, argv);

    wcout << L"for string we got : " << _stringTest << endl
         << L"for ulabeled one we got : " << _utest << endl
         << L"for ulabeled two we got : " << _ztest << endl
         << L"for bool B we got : " << _boolTestB << endl;
}

void parseOptions(int argc, wchar_t **argv) {
    try {
        CmdLine cmd(L"this is a message", L'=', L"0.99");

        //
        // Define arguments
        //

        SwitchArg btest(L"B", L"existTestB", L"exist Test B", cmd, false);

        ValueArg<wstring> stest(L"s", L"stringTest", L"string test", true, L"homer",
                               L"string", cmd);

        UnlabeledValueArg<wstring> utest(L"unTest1", L"unlabeled test one", true,
                                        L"default", L"string", cmd);

        UnlabeledValueArg<wstring> ztest(L"unTest2", L"unlabeled test two", true,
                                        L"default", L"string", cmd);

        MultiArg<int> itest(L"i", L"intTest", L"multi int test", false, L"int",
                            cmd);

        MultiArg<float> ftest(L"f", L"floatTest", L"multi float test", false,
                              L"float", cmd);

        UnlabeledMultiArg<wstring> mtest(L"fileName", L"file names", false,
                                        L"fileNameString", cmd);
        //
        // Parse the command line.
        //
        cmd.parse(argc, argv);

        //
        // Set variables
        //
        _stringTest = stest.getValue();
        _boolTestB = btest.getValue();
        _utest = utest.getValue();
        _ztest = ztest.getValue();

        vector<int> vi = itest.getValue();
        for (int i = 0; static_cast<unsigned int>(i) < vi.size(); i++)
            wcout << L"[-i] " << i << L"  " << vi[i] << endl;

        vector<float> vf = ftest.getValue();
        for (int i = 0; static_cast<unsigned int>(i) < vf.size(); i++)
            wcout << L"[-f] " << i << L"  " << vf[i] << endl;

        vector<wstring> v = mtest.getValue();
        for (int i = 0; static_cast<unsigned int>(i) < v.size(); i++)
            wcout << L"[  ] " << i << L"  " << v[i] << endl;

    } catch (ArgException &e) {
        wcout << L"ERROR: " << e.error() << L" " << e.argId() << endl;
    }
}
