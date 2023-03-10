// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

/******************************************************************************
 *
 *  file:  ArgException.h
 *
 *  Copyright (c) 2003, Michael E. Smoot .
 *  Copyright (c) 2017 Google LLC
 *  Copyright (c) 2022 Sergey Vasyutin .
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

#ifndef TCLAP_ARG_EXCEPTION_H
#define TCLAP_ARG_EXCEPTION_H

#include <exception>
#include <string>

namespace TCLAP {

/**
 * A simple class that defines and argument exception.  Should be caught
 * whenever a CmdLine is created and parsed.
 */
class ArgException : public std::exception {
public:
    /**
     * Constructor.
     * \param text - The text of the exception.
     * \param id - The text identifying the argument source.
     * \param td - Text describing the type of ArgException it is.
     * of the exception.
     */
    ArgException(const std::wstring &text = L"undefined exception",
                 const std::wstring &id = L"undefined",
                 const std::wstring &td = L"Generic ArgException")
        : std::exception(),
          _errorText(text),
          _argId(id),
          _typeDescription(td) {}

    /**
     * Destructor.
     */
    virtual ~ArgException() throw() {}

    /**
     * Returns the error text.
     */
    std::wstring error() const { return (_errorText); }

    /**
     * Returns the argument id.
     */
    std::wstring argId() const {
        if (_argId == L"undefined")
            return L" ";
        else
            return (L"Argument: " + _argId);
    }

    /**
     * Returns the arg id and error text.
     */
    const char *what() const throw() {
        static std::string ex;
        std::wstring wex(wwhat());
        ex.resize(wex.size());
        auto it_ex = ex.begin();
        for(auto it_wex = wex.cbegin(); it_wex != wex.cend(); ++it_wex, ++it_ex) 
           *it_ex = char(*it_wex);
        return ex.c_str();
    }

    /**
     * Returns the arg id and error text.
     */
    const wchar_t *wwhat() const throw() {
        static std::wstring ex;
        ex = _argId + L" -- " + _errorText;
        return ex.c_str();
    }

    /**
     * Returns the type of the exception.  Used to explain and distinguish
     * between different child exceptions.
     */
    std::wstring typeDescription() const { return _typeDescription; }

private:
    /**
     * The text of the exception message.
     */
    std::wstring _errorText;

    /**
     * The argument related to this exception.
     */
    std::wstring _argId;

    /**
     * Describes the type of the exception.  Used to distinguish
     * between different child exceptions.
     */
    std::wstring _typeDescription;
};

/**
 * Thrown from within the child Arg classes when it fails to properly
 * parse the argument it has been passed.
 */
class ArgParseException : public ArgException {
public:
    /**
     * Constructor.
     * \param text - The text of the exception.
     * \param id - The text identifying the argument source
     * of the exception.
     */
    ArgParseException(const std::wstring &text = L"undefined exception",
                      const std::wstring &id = L"undefined")
        : ArgException(text, id,
                       std::wstring(L"Exception found while parsing ") +
                           std::wstring(L"the value the Arg has been passed.")) {}
};

/**
 * Thrown from CmdLine when the arguments on the command line are not
 * properly specified, e.g. too many arguments, required argument missing, etc.
 */
class CmdLineParseException : public ArgException {
public:
    /**
     * Constructor.
     * \param text - The text of the exception.
     * \param id - The text identifying the argument source
     * of the exception.
     */
    CmdLineParseException(const std::wstring &text = L"undefined exception",
                          const std::wstring &id = L"undefined")
        : ArgException(text, id,
                       std::wstring(L"Exception found when the values ") +
                           std::wstring(L"on the command line do not meet ") +
                           std::wstring(L"the requirements of the defined ") +
                           std::wstring(L"Args.")) {}
};

/**
 * Thrown from Arg and CmdLine when an Arg is improperly specified, e.g.
 * same flag as another Arg, same name, etc.
 */
class SpecificationException : public ArgException {
public:
    /**
     * Constructor.
     * \param text - The text of the exception.
     * \param id - The text identifying the argument source
     * of the exception.
     */
    SpecificationException(const std::wstring &text = L"undefined exception",
                           const std::wstring &id = L"undefined")
        : ArgException(text, id,
                       std::wstring(L"Exception found when an Arg object ") +
                           std::wstring(L"is improperly defined by the ") +
                           std::wstring(L"developer.")) {}
};

/**
 * Thrown when TCLAP thinks the program should exit.
 *
 * For example after parse error this exception will be thrown (and
 * normally caught). This allows any resource to be clened properly
 * before exit.
 *
 * If exception handling is disabled (CmdLine::setExceptionHandling),
 * this exception will propagate to the call site, allowing the
 * program to catch it and avoid program termination, or do it's own
 * cleanup. See for example, https://sourceforge.net/p/tclap/bugs/29.
 */
class ExitException {
public:
    explicit ExitException(int estat) : _estat(estat) {}

    int getExitStatus() const { return _estat; }

private:
    int _estat;
};

}  // namespace TCLAP

#endif  // TCLAP_ARG_EXCEPTION_H
