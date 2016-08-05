#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

#include "headers/elfheader.h"
#include "headers/programheader.h"

using namespace std;

void bail(string message);

int main(int argc, char * argv[]) {
    if (argc < 2)
        bail(string("Usage: ") + string(argv[0]) + string(" <elffile>"));

    fstream file(argv[1], ios_base::in | ios_base::binary);
    if (!file.is_open())
        bail(string("Failed to load ") + string(argv[1]));

    auto header = ElfHeader(file);
    file.seekg(header.program_offset);
    auto progHeader = ProgramHeader(file, header.bitness, header.endianess);

    file.close();

    cout << header.toString();
    cout << endl << endl;
    cout << progHeader.toString();
    cout << endl;

    return 0;
}

void bail(string message) {
    cout << message << endl;
    exit(1);
}
