// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include "wtclap/CmdLine.h"
#include <iterator>
#include <algorithm>

#include <sstream>

namespace TCLAP {
template <>
struct ArgTraits<std::vector<double> > {
    typedef StringLike ValueCategory;
};

template <>
void SetString<std::vector<double> >(std::vector<double> &v,
                                     const std::wstring &s) {
    std::wistringstream iss(s);
    while (iss) {
        double tmp;
        iss >> tmp;
        v.push_back(tmp);
    }
}
}

int wmain(int argc, wchar_t *argv[]) {
    TCLAP::CmdLine cmd(L"Command description message", L' ', L"0.9");
    TCLAP::ValueArg<std::vector<double> > vec(
        L"v", L"vect", L"vector", true, std::vector<double>(), L"3D vector", cmd);
    try {
        cmd.parse(argc, argv);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    const std::vector<double> &v = vec.getValue();
    std::copy(v.begin(), v.end(),
              std::ostream_iterator<double, wchar_t>(std::wcout, L"\n"));
    std::wcout << std::endl;
}
