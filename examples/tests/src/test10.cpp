// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

// Test only makes sure we can use different argv types for the
// parser. Don't run, just compile.

#include "wtclap/CmdLine.h"

using namespace TCLAP;
int main() {
    wchar_t *argv5[] = {(wchar_t *)L"Foo", 0};
    const wchar_t *argv6[] = {L"Foo", 0};
    const wchar_t *const argv7[] = {L"Foo", 0};
    wchar_t **argv1 = argv5;
    const wchar_t **argv2 = argv6;
    const wchar_t *const *argv3 = argv7;
    const wchar_t *const *const argv4 = argv7;

    CmdLine cmd(L"Command description message", L' ', L"0.9");
    cmd.parse(0, argv1);
    cmd.parse(0, argv2);
    cmd.parse(0, argv3);
    cmd.parse(0, argv4);
    cmd.parse(0, argv5);
    cmd.parse(0, argv6);
    cmd.parse(0, argv7);
}
