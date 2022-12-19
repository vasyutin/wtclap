#include <wtclap/CmdLine.h>

#include <iostream>

int wmain() {
  {
    TCLAP::CmdLine cmd(L"First example");
    TCLAP::SwitchArg first_arg(L"f", L"first", L"first switch argument", cmd);
    TCLAP::SwitchArg second_arg(L"s", L"second", L"second switch argument", cmd);

    int first_argc = 3;
    const wchar_t** first_argv = new const wchar_t* [first_argc];
    first_argv[0] = L"/nowhere";
    first_argv[1] = L"--first";
    first_argv[2] = L"--";
    cmd.parse(first_argc,
	      first_argv);
    delete[] first_argv;

    std::cout << L"First example: first=" << first_arg.getValue()
	      << L", second=" << second_arg.getValue() << std::endl;
  }

  {
    TCLAP::CmdLine cmd(L"Second example");
    TCLAP::SwitchArg first_arg(L"f", L"first", L"first switch argument", cmd);
    TCLAP::SwitchArg second_arg(L"s", L"second", L"second switch argument", cmd);

    int second_argc = 3;
    const wchar_t** second_argv = new const wchar_t* [second_argc];
    second_argv[0] = L"/nowhere";
    second_argv[1] = L"--second";
    second_argv[2] = L"--";
    cmd.parse(second_argc,
	      second_argv);
    delete[] second_argv;

    std::wcout << L"Second example: first=" << first_arg.getValue()
	      << L", second=" << second_arg.getValue() << std::endl;
  }
  
  return 0;
}
