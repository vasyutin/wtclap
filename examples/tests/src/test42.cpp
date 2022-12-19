/******************************************************************************
 *
 *  Copyright (c) 2019 Google LLC.
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
/**
 * Usage statements should look like the manual pages.  Options w/o
 * operands come first, in alphabetical order inside a single set of
 * braces, upper case before lower case (AaBbCc...).  Next are options
 * with operands, in the same order, each in braces.  Then required
 * arguments in the order they are specified, followed by optional
 * arguments in the order they are specified.  A bar (`|') separates
 * either/or options/arguments, and multiple options/arguments which
 * are specified together are placed in a single set of braces.
 *
 * Use getprogname() instead of hardcoding the program name.
 *
 * "usage: f [-aDde] [-b b_arg] [-m m_arg] req1 req2 [opt1 [opt2]]\n"
 * "usage: f [-a | -b] [-c [-de] [-n number]]\n"
 */
int wmain(int argc, wchar_t **argv) {
    try {
        // "usage: f [-a | -b] [-c [-de] [-n number]]\n"
        CmdLine cmd(L"");
        EitherOf aorb(cmd);
        SwitchArg a(L"a", L"aopt", L"a", aorb);
        SwitchArg b(L"b", L"bopt", L"b", aorb);

        AnyOf other(cmd);
        SwitchArg c(L"c", L"copt", L"c", other);
        SwitchArg d(L"d", L"dopt", L"d", other);
        SwitchArg e(L"e", L"eopt", L"e", other);
        ValueArg<int> n_arg(L"n", L"narg", L"n_arg", false, 4711, L"number", other);

        OneOf x(cmd);
        SwitchArg f(L"f", L"fopt", L"f", x);
        SwitchArg g(L"", L"gopt", L"g", x);

        UnlabeledValueArg<int> req1(L"req1", L"req_1", true, 47, L"int", cmd);

        cmd.parse(argc, argv);

    } catch (SpecificationException &e) {
        // Expected
        std::wcout << e.what() << std::endl;
    }
}
