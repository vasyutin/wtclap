// Example based on question in https://sourceforge.net/p/tclap/support-requests/2/
//
// Shows how to use a pair as a "custom type". Note that the argument
// flag must be specified, like -p "1 2.3" (with quotes).

#include <iostream>
#include <utility>

// We need to tell TCLAP how to parse our pair, we assume it will be
// given as two arguments separated by whitespace.
std::wistream &operator>>(std::wistream &is, std::pair<int, double> &p) {
  return is >> p.first >> p.second;
}

// Make it easy to print values of our type.
std::wostream &operator<<(std::wostream &os, const std::pair<int, double> &p) {
  return os << p.first << ' ' << p.second;
}

#include "wtclap/CmdLine.h"

using namespace TCLAP;

// Our pair can now be used as any other type.
int wmain(int argc, wchar_t **argv) {
  CmdLine cmd(L"test pair argument");
  ValueArg<std::pair<int, double> > parg(L"p", L"pair", L"int,double pair",
                                         true,
                                         std::make_pair(0, 0.0),
                                         L"int,double",
                                         cmd);
  cmd.parse(argc, argv);
  std::wcout << parg.getValue() << std::endl;
}
