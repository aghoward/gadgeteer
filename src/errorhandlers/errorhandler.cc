#include "errorhandler.h"

#include <iostream>
#include <fstream>
#include <execinfo.h>
#include <string>
#include <vector>
#include <exception>
#include <signal.h>
#include <cstring>
#include <cstdlib>
#include <ostream>
#include <map>
#include <functional>

using namespace std;

ErrorHandler::ErrorHandler() {
    _oldSignalHandlers = map<int, function<void (int)>>();
    _oldSigActionHandlers = map<int, function<void (int, siginfo_t*, void*)>>();
}

void ErrorHandler::RegisterExceptionHandler(function<void ()> handler) {
    auto ret = set_terminate(*handler.target<void (*)()>());
}

void ErrorHandler::RegisterSignal(int interrupt, function<void (int)> handler) {
    struct sigaction oldAction, newAction;

    ZeroAction(&oldAction);
    ZeroAction(&newAction);

    newAction.sa_handler = *handler.target<void (*)(int)>();

    auto status = sigaction(interrupt, &newAction, &oldAction);

    if (status) {
        cerr << "Failed to register signal handler `" << strsignal(interrupt) << "`: " << strerror(errno) << endl;
    } else {
        _oldSignalHandlers[interrupt] = oldAction.sa_handler;
    }
}

void ErrorHandler::RegisterSignal(int interrupt, function<void (int, siginfo_t*, void*)> handler) {
    struct sigaction oldAction, newAction;

    ZeroAction(&oldAction);
    ZeroAction(&newAction);

    newAction.sa_sigaction = *handler.target<void (*)(int, siginfo_t*, void*)>();

    auto status = sigaction(interrupt, &newAction, &oldAction);

    if (status) {
        cerr << "Failed to register signal handler `" << strsignal(interrupt) << "`: " << strerror(errno) << endl;
    } else {
        _oldSigActionHandlers[interrupt] = oldAction.sa_sigaction;
    }
}

void ErrorHandler::RegisterSignals(vector<int> signals, function<void (int)> handler) {
    for (auto it = signals.begin(); it != signals.end(); it++)
        RegisterSignal(*it, handler);
}

void ErrorHandler::RegisterSignals(vector<int> signals, function<void (int, siginfo_t*, void*)> handler) {
    for (auto it = signals.begin(); it != signals.end(); it++)
        RegisterSignal(*it, handler);
}

void ErrorHandler::ZeroAction(struct sigaction *action) {
    action->sa_handler = NULL;
    action->sa_flags = action->sa_flags ^ action->sa_flags;
    action->sa_sigaction = NULL;
}

void ErrorHandler::UnregisterSignals(vector<int> signals) {
    for (auto it = signals.begin(); it != signals.end(); it++) {
        if (_oldSignalHandlers.count(*it)) 
            RegisterSignal(*it, _oldSignalHandlers[*it]);
        else if (_oldSigActionHandlers.count(*it))
            RegisterSignal(*it, _oldSigActionHandlers[*it]);
    }
}


