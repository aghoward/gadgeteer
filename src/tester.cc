#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <signal.h>
#include <exception>

#include "utils.h"
#include "qvector.h"
#include "errorhandler.h"
#include "handlers.h"

#include "failurereasons.h"
#include "fileparser.h"
#include "binaryfile.h"
#include "gadgetfinder.h"

using namespace std;

void registerErrorHandlers();
void bail(string message);
string convertFailureReason(ParseFailure reason);
void printInformation(BinaryFile binaryFile);


int main(int argc, char * argv[]) {
    registerErrorHandlers();

    if (argc < 2)
        bail(string("Usage: ") + string(argv[0]) + string(" <elffile>"));

    auto result = FileParser::Create(argv[1]);

    result.Match<void>(
        printInformation,
        [] (ParseFailure reason) { bail(convertFailureReason(reason)); }
    );

    return 0;
}


void registerErrorHandlers() {
    auto signals = vector<int>();
    auto errorHandler = ErrorHandler();

    signals.push_back(SIGINT);
    signals.push_back(SIGSEGV);
    signals.push_back(SIGILL);

    errorHandler.RegisterSignals(signals, DefaultSignalHandler);
    errorHandler.RegisterExceptionHandler(DefaultExceptionHandler);
}

void printInformation(BinaryFile fileInfo) {
    cout << "total headers: " << fileInfo.section_headers.size() << endl;

    auto matches = GadgetFinder::FindGadget(fileInfo, string("\x52\xc3"));
    auto distinctHeaders = matches.distinct<string>([] (auto header) { return header.header.name; });

    cout << "Found " << matches.size() << " matches" << endl;
    cout << "Found " << distinctHeaders.size() << " distinct header matches" << endl;

    for (auto header = distinctHeaders.begin(); header != distinctHeaders.end(); header++ )
        cout << header->header.name << ": " << to_hex(header->offset) << endl;

}

void bail(string message) {
    cout << message << endl;
    exit(1);
}

string convertFailureReason(ParseFailure reason) {
    switch(reason) {
        case FileReadError:
            return "I/O error on file";
            break;
        case InvalidFileFormat:
            return "Invalid file format";
            break;
        case FileDoesNotExist:
            return "File does not exist";
            break;
        default:
            return "Unknown failure reason";
    }
}
