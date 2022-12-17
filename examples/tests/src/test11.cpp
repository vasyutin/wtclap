// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include "wtclap/CmdLine.h"
#include <iterator>

#include <sstream>

using namespace TCLAP;

// Define a simple 3D vector type
struct Vect3D {
    double v[3];

    // operator= will be used to assign to the vector
    Vect3D &operator=(const std::wstring &str) {
        std::wistringstream iss(str);
        if (!(iss >> v[0] >> v[1] >> v[2]))
            throw TCLAP::ArgParseException(str + L" is not a 3D vector");

        return *this;
    }

    std::wostream &print(std::wostream &os) const {
        std::copy(v, v + 3, std::ostream_iterator<double, wchar_t>(os, L" "));
        return os;
    }
};

// Create an ArgTraits for the 3D vector type that declares it to be
// of string like type
namespace TCLAP {
template <>
struct ArgTraits<Vect3D> {
    typedef StringLike ValueCategory;
};
}

int wmain(int argc, wchar_t *argv[]) {
    CmdLine cmd(L"Command description message", L' ', L"0.9");
    ValueArg<Vect3D> vec(L"v", L"vect", L"vector", true, Vect3D(), L"3D vector",
                         cmd);

    try {
        cmd.parse(argc, argv);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    vec.getValue().print(std::wcout);
    std::cout << std::endl;
}
