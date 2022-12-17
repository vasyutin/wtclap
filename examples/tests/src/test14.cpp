// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include "wtclap/CmdLine.h"
#include <iterator>
#include <algorithm>

#include <sstream>

// Define a simple 3D vector type
template <typename T, size_t LEN>
struct Vect : public TCLAP::StringLikeTrait {
    // typedef TCLAP::StringLike ValueCategory;
    T v[LEN];

    // operator= will be used to assign to the vector
    Vect &operator=(const std::wstring &str) {
        std::wistringstream iss(str);
        for (size_t n = 0; n < LEN; n++) {
            if (!(iss >> v[n])) {
                std::wostringstream oss;
                oss << " is not a vector of size " << LEN;
                throw TCLAP::ArgParseException(str + oss.str());
            }
        }

        if (!iss.eof()) {
            std::wostringstream oss;
            oss << " is not a vector of size " << LEN;
            throw TCLAP::ArgParseException(str + oss.str());
        }

        return *this;
    }

    std::wostream &print(std::wostream &os) const {
        std::copy(v, v + LEN, std::ostream_iterator<T, wchar_t>(os, L", "));
        return os;
    }
};

int wmain(int argc, wchar_t *argv[]) {
    TCLAP::CmdLine cmd(L"Command description message", L' ', L"0.9");
    TCLAP::ValueArg<Vect<double, 3> > vec(L"v", L"vect", L"vector", true,
                                          Vect<double, 3>(), L"3D vector", cmd);

    try {
        cmd.parse(argc, argv);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    vec.getValue().print(std::wcout);
    std::cout << std::endl;
}
