// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

/******************************************************************************
 *
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
#include "wtclap/DocBookOutput.h"

using namespace TCLAP;

int wmain(int argc, wchar_t **argv) {
    DocBookOutput output;
    CmdLine cmd(L"");
    cmd.setOutput(&output);

    ValueArg<int> arg0(L"a", L"a_int", L"int arg", false, 4711, L"int", cmd);
    ValueArg<int> arg1(L"b", L"b_int", L"int arg", false, 4711, L"int", cmd);
    arg1.hideFromHelp();

    ValueArg<int> arg2(L"c", L"c_int", L"int arg", false, 4711, L"int");
    arg2.hideFromHelp();
    ValueArg<int> arg3(L"d", L"d_int", L"int arg", false, 4711, L"int");
    arg3.hideFromHelp();

    if (argc > 2) {
        arg2.hideFromHelp(false);
    }

    cmd.xorAdd(arg2, arg3);
    cmd.parse(argc, argv);
}
