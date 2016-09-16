#include "handlers.h"

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

    for (auto i = 0; i < actualSize; i++)
        ret.push_back(string(symbols[i]));

    return ret;
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
}

void DefaultExceptionHandler() {
    ExceptionHandler(BACKTRACE_SIZE);
}
