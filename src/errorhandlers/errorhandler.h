#ifndef ErrorHandler_H
#define ErrorHandler_H

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <signal.h>

using namespace std;

class ErrorHandler {
    private:
        map<int, function<void (int)>> _oldSignalHandlers;
        map<int, function<void (int, siginfo_t *, void *)>> _oldSigActionHandlers;

        void ZeroAction(struct sigaction *action);

    public:
        ErrorHandler();

        void RegisterExceptionHandler(function<void ()> handler);

        void RegisterSignal(int interrupt, function<void (int)> handler);
        void RegisterSignal(int interrupt, function<void (int, siginfo_t*, void*)> handler);
        void RegisterSignals(vector<int> signals, function<void (int)> handler);
        void RegisterSignals(vector<int> signals, function<void (int, siginfo_t*, void*)> handler);

        void UnregisterSignals(vector<int> signals);
};

#endif
