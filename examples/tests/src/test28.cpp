#include <iostream>

#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain() {
    try {
        CmdLine cmd(L"test constraint bug");
        ValueArg<int> arg(L"i", L"int", L"tests int arg", false, 4711, NULL, cmd);
        wcout << L"Expected exception" << endl;
    } catch (std::logic_error &) { /* expected */
    }

    try {
        CmdLine cmd(L"test constraint bug");
        ValueArg<int> arg1(L"i", L"int", L"tests int arg", false, 4711, NULL,
                           NULL);
        wcout << L"Expected exception" << endl;
    } catch (std::logic_error &) { /* expected */
    }

    try {
        CmdLine cmd(L"test constraint bug");
        MultiArg<int> arg1(L"i", L"int", L"tests int arg", false, NULL, NULL);
        wcout << L"Expected exception" << endl;
    } catch (std::logic_error &) { /* expected */
    }

    try {
        CmdLine cmd(L"test constraint bug");
        MultiArg<int> arg1(L"i", L"int", L"tests int arg", false, NULL, cmd);
        wcout << L"Expected exception" << endl;
    } catch (std::logic_error &) { /* expected */
    }

    wcout << L"Passed" << endl;
}
