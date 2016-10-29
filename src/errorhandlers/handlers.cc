#include "handlers.h"

#include <cxxabi.h>
#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include <exception>
#include <cstring>
#include <execinfo.h>

using namespace std;

const int BACKTRACE_SIZE = 200;


void PrintBacktrace(vector<string> symbols) {
    for (auto it = symbols.begin(); it != symbols.end(); it++)
        cerr << *it << endl;
}

vector<string> GetBacktrace(int backtraceSize) {
    void * buffer[backtraceSize];
    vector<string> ret;
    
    auto actualSize = backtrace(buffer, backtraceSize);
    auto symbols = backtrace_symbols(buffer, actualSize);

    for (auto i = 0; i < actualSize; i++) {
        ret.push_back(GetFriendlyName(symbols[i]));
    }

    return ret;
}

string GetFriendlyName(char * fullname) {
    auto manstr = string(fullname);
    auto mangledName = GetSubstring(manstr, '(', '+');
    auto offset = GetSubstring(manstr, '+', ')');
    auto file = GetOriginatingFile(manstr);

    if (mangledName == string())
        return string(fullname);

    auto demangled = Demangle(mangledName);
    return file + " " + demangled + "+" + offset;
}

string Demangle(string mangled) {
    int status;
    auto demangled = abi::__cxa_demangle(mangled.c_str(), 0, 0, &status);
    if (status)
        return mangled;
    return string(demangled);
}

string GetOriginatingFile(string fullname) {
    auto len = fullname.find('(');
    return fullname.substr(0, len);
}

string GetSubstring(string full, char begin, char end) {
    auto bidx = full.find(begin) + 1;
    auto eidx = full.find(end) - 1;
    auto len = eidx - bidx + 1;
    return full.substr(bidx, len);
}

void ExceptionHandler(int backtraceSize) {
    auto currException = current_exception();

    try {
        if (currException)
            rethrow_exception(currException);
    } catch (exception &e) {
        cerr << e.what();
        PrintBacktrace(GetBacktrace(backtraceSize));
    }

    abort();
}

void InterruptHandler(int interrupt, int backtraceSize) {
    cerr << "Interrupted with " << strsignal(interrupt) << endl;
    PrintBacktrace(GetBacktrace(backtraceSize));
}

void DefaultSignalHandler(int signal) {
    InterruptHandler(signal, BACKTRACE_SIZE);
    abort();
}

void DefaultExceptionHandler() {
    ExceptionHandler(BACKTRACE_SIZE);
}
