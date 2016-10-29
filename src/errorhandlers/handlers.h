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
string GetFriendlyName(char * mangled);
string GetSubstring(string full, char begin, char end);
string GetOriginatingFile(string fullname);
string Demangle(string mangled);
void ExceptionHandler(int backtraceSize);
void InterruptHandler(int interrupt, int backtraceSize);
void DefaultSignalHandler(int signal);
void DefaultExceptionHandler();
#endif
