#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

#include "utils.h"
#include "qvector.h"

#include "failurereasons.h"
#include "fileparser.h"
#include "binaryfile.h"

using namespace std;

void bail(string message);
string convertFailureReason(ParseFailure reason);
void printInformation(BinaryFile binaryFile);

int main(int argc, char * argv[]) {
    if (argc < 2)
        bail(string("Usage: ") + string(argv[0]) + string(" <elffile>"));

    auto result = FileParser::Create(argv[1]);

    result.Match<void>(
        printInformation,
        [] (ParseFailure reason) { bail(convertFailureReason(reason)); }
    );

    return 0;
}

void printInformation(BinaryFile fileInfo) {
    cout << fileInfo.elf_header.toString();
    cout << endl << endl;

    cout << "Creating progSections" << endl;
    auto progSections = fileInfo.section_headers.where([] (auto header) { return header.type == SECT_PROGRAM; });
    cout << "Createing execSections" << endl;
    auto execSections = progSections.where([] (auto header) { return header.flags & SECT_EXECUTE; });

    cout << "Program Section count: " << progSections.size() << endl;
    cout << "Executable Section count: " << execSections.size() << endl;

    auto tofind = string("\xff\x35");
    for (auto it = execSections.begin(); it != execSections.end(); it++) {
        cout << it->toString() << endl << endl;
        auto offset = it->contents.find(tofind);
        cout << "Found bytes at offset: " << utils::to_hex(it->address + offset) << endl << endl;
    }
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
