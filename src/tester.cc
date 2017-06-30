#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <signal.h>
#include <exception>

#include "utils.h"
#include "queryalgorithms.h"
#include "errorhandler.h"
#include "handlers.h"

#include "failurereasons.h"
#include "fileparser.h"
#include "binaryfile.h"
#include "gadgetfinder.h"
#include "assemblyparserfactory.h"

#include "gadgeteermodule.h"
#include "cdif/cdif.h"

using namespace std;

const string OPCODE_FILE = "opcodes.json";
const string REGISTER_FILE = "registers.json";

void registerErrorHandlers();
void bail(string message);
string convertFailureReason(ParseFailure reason);
void printInformation(shared_ptr<BinaryFile> binaryFile, string toFind);


int main(int argc, char * argv[]) {
    registerErrorHandlers();

    if (argc < 3)
        bail(string("Usage: ") + string(argv[0]) + string(" <elffile> <toFind>"));

    auto container = cdif::Container();
    container.RegisterModule<GadgeteerModule>();
    auto fileParser = container.Resolve<FileParser>();

    auto result = fileParser.Create(argv[1]);
    auto toFind = string(argv[2]);

    result.Match<void>(
        [toFind] (auto fileInfo) { printInformation(fileInfo, toFind); },
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

void printInformation(shared_ptr<BinaryFile> fileInfo, string toFind) {
    cout << "total headers: " << fileInfo->section_headers.size() << endl;
    
    auto assemblyParser = AssemblyParserFactory::create(OPCODE_FILE, REGISTER_FILE);
    auto assemblies = assemblyParser.getBinaryString(toFind);
    cout << "Total number of assemblies: " << assemblies.size() << endl;
    auto gadgets = GadgetFinder::FindAllGadgets(fileInfo, assemblies);

    cout << "Found " << gadgets.size() << " matches" << endl;
    for (auto header = gadgets.begin(); header != gadgets.end(); header++ )
        cout << header->header->name << ": " << to_hex(header->offset) << endl;
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
