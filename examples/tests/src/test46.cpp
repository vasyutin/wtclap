#include "wtclap/CmdLine.h"
#include <vector>
#include <string>

using namespace TCLAP;
using namespace std;

// https://sourceforge.net/p/tclap/bugs/30/
int wmain() {
  CmdLine cmd(L"test empty argv");
  std::vector<wstring> args;
  cmd.parse(args);
}
