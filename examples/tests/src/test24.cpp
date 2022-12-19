// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

// Test various Arg properties such as invalid flag/names

#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain() {
    CmdLine cmd(L"Command description message", L' ', L"0.9");
    try {  // Argument with two character 'flag'
        ValueArg<wstring> nameArg(L"nx", L"name", L"Name to print", true, L"homer",
                                 L"string");
        return EXIT_FAILURE;
    } catch (SpecificationException &e) {
        wcout << e.what() << std::endl;  // Expected
    }

    try {  // space as flag
        ValueArg<wstring> nameArg(L" ", L"name", L"Name to print", true, L"homer",
                                 L"string");
        return EXIT_FAILURE;
    } catch (SpecificationException &e) {
        wcout << e.what() << std::endl;  // Expected
    }

    try {  // - as flag
        ValueArg<wstring> nameArg(L"-", L"name", L"Name to print", true, L"homer",
                                 L"string");
        return EXIT_FAILURE;
    } catch (SpecificationException &e) {
        wcout << e.what() << std::endl;  // Expected
    }

    try {  // -- as flag
        ValueArg<wstring> nameArg(L"--", L"name", L"Name to print", true, L"homer",
                                 L"string");
        return EXIT_FAILURE;
    } catch (SpecificationException &e) {
        wcout << e.what() << std::endl;  // Expected
    }

    try {  // space as name
        ValueArg<wstring> nameArg(L"n", L" ", L"Name to print", true, L"homer",
                                 L"string");
        return EXIT_FAILURE;
    } catch (SpecificationException &e) {
        wcout << e.what() << std::endl;  // Expected
    }

    try {  // - as flag
        ValueArg<wstring> nameArg(L"n", L"-", L"Name to print", true, L"homer",
                                 L"string");
        return EXIT_FAILURE;
    } catch (SpecificationException &e) {
        wcout << e.what() << std::endl;  // Expected
    }

    try {  // -- as flag
        ValueArg<wstring> nameArg(L"n", L"--", L"Name to print", true, L"homer",
                                 L"string");
        return EXIT_FAILURE;
    } catch (SpecificationException &e) {
        wcout << e.wwhat() << std::endl;  // Expected
    }
}
