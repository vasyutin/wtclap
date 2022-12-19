#include "wtclap/CmdLine.h"
#include <iterator>

using namespace TCLAP;

// Define a simple 3D vector type
struct Vect3D {
    double v[3];

    std::wostream &print(std::wostream &os) const {
        std::copy(v, v + 3, std::ostream_iterator<double, wchar_t>(os, L" "));
        return os;
    }
};

// operator>> will be used to assign to the vector since the default
// is that all types are ValueLike.
std::wistream &operator>>(std::wistream &is, Vect3D &v) {
    if (!(is >> v.v[0] >> v.v[1] >> v.v[2]))
        throw TCLAP::ArgParseException(L" Argument is not a 3D vector");

    return is;
}

int wmain(int argc, wchar_t *argv[]) {
    CmdLine cmd(L"Command description message", L' ', L"0.9");
    ValueArg<Vect3D> vec(L"v", L"vect", L"vector", true, Vect3D(), L"3D vector",
                         cmd);

    try {
        cmd.parse(argc, argv);
    } catch (std::exception &e) {
        std::wcout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    vec.getValue().print(std::wcout);
    std::wcout << std::endl;
}
