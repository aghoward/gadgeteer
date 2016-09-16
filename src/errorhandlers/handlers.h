#ifndef Handlers_H
#define Handlers_H

#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include <exception>
#include <cstring>
#include <execinfo.h>

using namespace std;

void PrintBacktrace(vector<string> symbols);
vector<string> GetBacktrace(int backtraceSize);
void ExceptionHandler(int backtraceSize);
void InterruptHandler(int interrupt, int backtraceSize);
void DefaultSignalHandler(int signal);
void DefaultExceptionHandler();
#endif
