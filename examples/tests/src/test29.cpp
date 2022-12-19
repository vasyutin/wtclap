// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

/******************************************************************************
 *
 *  file:  Arg.h
 *
 *  Copyright (c) 2003, Michael E. Smoot .
 *  Copyright (c) 2004, Michael E. Smoot, Daniel Aarno .
 *  Copyright (c) 2017 Google LLC.
 *  All rights reserved.
 *
 *  See the file COPYING in the top directory of this distribution for
 *  more information.
 *
 *  THE SOFTWARE IS PROVIDED _AS IS_, WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/

#include "wtclap/CmdLine.h"

using namespace TCLAP;

int wmain(int argc, wchar_t **argv) {
    CmdLine cmd(L"");
    ValueArg<int> arg0(L"a", L"a_int", L"first int arg", false, 4711, L"int");
    ValueArg<int> arg1(L"b", L"b_int", L"second int arg", false, 4711, L"int");
    ValueArg<std::wstring> arg2(L"s", L"str", L"string arg", false, L"foo", L"str");

    EitherOf input;
    input.add(arg0).add(arg1).add(arg2);

    cmd.add(input);
    cmd.parse(argc, argv);

    if (arg0.isSet()) {
        std::wcout << L"a_int was set to: " << arg0.getValue() << std::endl;
    }
    if (arg1.isSet()) {
        std::wcout << L"b_int was set to: " << arg1.getValue() << std::endl;
    }
    if (arg2.isSet()) {
        std::wcout << L"str was set to: " << arg2.getValue() << std::endl;
    }
}
