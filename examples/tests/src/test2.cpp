// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include "wtclap/CmdLine.h"
#include <iostream>
#include <string>

using namespace TCLAP;
using namespace std;

int _intTest;
double _floatTest;
bool _boolTestA;
bool _boolTestB;
bool _boolTestC;
wstring _stringTest;
wstring _utest;

void parseOptions(int argc, wchar_t **argv);

int wmain(int argc, wchar_t **argv) {
    parseOptions(argc, argv);

    wcout << L"for float we got : " << _floatTest << endl
         << L"for int we got : " << _intTest << endl
         << L"for string we got : " << _stringTest << endl
         << L"for ulabeled we got : " << _utest << endl
         << L"for bool A we got : " << _boolTestA << endl
         << L"for bool B we got : " << _boolTestB << endl
         << L"for bool C we got : " << _boolTestC << endl;
}

void parseOptions(int argc, wchar_t **argv) {
    try {
        CmdLine cmd(L"this is a message", L' ', L"0.99");

        //
        // Define arguments
        //

        SwitchArg btest(L"B", L"existTestB", L"tests for the existence of B",
                        false);
        cmd.add(btest);

        SwitchArg ctest(L"C", L"existTestC", L"tests for the existence of C",
                        false);
        cmd.add(ctest);

        SwitchArg atest(L"A", L"existTestA", L"tests for the existence of A",
                        false);
        cmd.add(atest);

        ValueArg<wstring> stest(L"s", L"stringTest", L"string test", true, L"homer",
                               L"string");
        cmd.add(stest);

        ValueArg<int> itest(L"i", L"intTest", L"integer test", true, 5, L"int");
        cmd.add(itest);

        ValueArg<double> ftest(L"f", L"floatTest", L"float test", false, 3.7,
                               L"float");
        cmd.add(ftest);

        UnlabeledValueArg<wstring> utest(L"unTest", L"unlabeld test", true,
                                        L"default", L"string");
        cmd.add(utest);

        UnlabeledMultiArg<wstring> mtest(L"fileName", L"file names", false,
                                        L"string");
        cmd.add(mtest);

        //
        // Parse the command line.
        //
        cmd.parse(argc, argv);

        //
        // Set variables
        //
        _intTest = itest.getValue();
        _floatTest = ftest.getValue();
        _stringTest = stest.getValue();
        _boolTestB = btest.getValue();
        _boolTestC = ctest.getValue();
        _boolTestA = atest.getValue();
        _utest = utest.getValue();

        vector<wstring> v = mtest.getValue();
        for (int i = 0; static_cast<unsigned int>(i) < v.size(); i++)
            wcout << i << L"  " << v[i] << endl;

    } catch (ArgException &e) {
        wcout << L"ERROR: " << e.error() << " " << e.argId() << endl;
    }
}
