/*
From: https://sourceforge.net/p/tclap/patches/16/

If any of the output strings formatted by spacePrintf (StdOutput.h)
contains a manual linebreak (\n), an empty line (i.e. two line breaks)
will be printed.

Desired behaviour would be that the line break is not duplicated. If
the user wants to print an empty line, they can put in two
linebreaks. Also, after a manual linebreak, any blanks entered by the
user (for example for manual indenting) should be preserved.
*/

#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t *argv[]) {
    CmdLine cmd(
        L"This is a program with a quite elaborate description\nAs it is so "
        L"long we use multiple lines.\nBut these are so far apart.\nEven though "
        L"I want only one line break");
    cmd.parse(argc, argv);
}
