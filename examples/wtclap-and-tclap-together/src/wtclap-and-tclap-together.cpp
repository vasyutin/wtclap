/******************************************************************************
 *
 *  file: wtclap-and-tclap-together.cpp
 *
 *  Copyright (c) 2022 Sergey Vasyutin.
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
#include <string>
#include <fstream>

#ifdef _MSC_VER
	#include <wtclap/CmdLine.h>
	typedef std::wstring TclapString;
	inline std::wostream& ErrorStream() {return std::wcerr;}
#else
	#include <tclap/CmdLine.h>
	#define TCLAP_STR(S_) S_
	typedef std::string TclapString;
	inline std::ostream& ErrorStream() {return std::cerr;}
#endif

//---------------------------------------------------------------------------
int WriteFile(const TclapString& FileName_)
{
	std::ofstream File(FileName_);
	return File? 0: 1;
}

//---------------------------------------------------------------------------
#ifdef _MSC_VER
int wmain(int Argc_, wchar_t *Argv_[])
#else
int main(int Argc_, char *Argv_[])
#endif
{
	TCLAP::CmdLine CmdParser(TCLAP_STR("Example of using TCALP and WTCALP in one source file."), TCLAP_STR(' '), TCLAP_STR("0.1"));
	TCLAP::ValueArg<TclapString> OutputFile(TCLAP_STR("f"), TCLAP_STR("file"), TCLAP_STR("Output filename"), true, TclapString(), TCLAP_STR("file"), CmdParser);

	try {
		CmdParser.parse(Argc_, Argv_);
	}
	catch(const TCLAP::ArgException &Exeption_) {
		ErrorStream() << TCLAP_STR("error: ") << Exeption_.error() << TCLAP_STR(" for arg ") << Exeption_.argId() << std::endl;
		return 1;
	}

	return WriteFile(OutputFile.getValue());
}