#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

#include "utils.h"

#include "elfheader.h"
#include "programheader.h"
#include "programheaderfactory.h"
#include "sectionheader.h"
#include "sectionheaderfactory.h"

using namespace std;

void bail(string message);

int main(int argc, char * argv[]) {
    if (argc < 2)
        bail(string("Usage: ") + string(argv[0]) + string(" <elffile>"));

    fstream file(argv[1], ios_base::in | ios_base::binary);
    if (!file.is_open())
        bail(string("Failed to load ") + string(argv[1]));

    auto header = ElfHeader(file);
    auto programheaders = ProgramHeaderFactory::Create(file, header);
    auto sectionheaders = SectionHeaderFactory::Create(file, header);
    file.close();

    cout << header.toString();
    cout << endl << endl;

    auto progSections = utils::where<SectionHeader>(sectionheaders, [] (auto header) { return header.type == SECT_PROGRAM; });
    auto execSections = utils::where<SectionHeader>(progSections, [] (auto header) { return header.flags & SECT_EXECUTE; });

    cout << "Program Section count: " << progSections.size() << endl;
    cout << "Executable Section count: " << execSections.size() << endl;

    auto tofind = string("\xff\x35");
    for (auto it = execSections.begin(); it != execSections.end(); it++) {
        cout << it->toString() << endl << endl;
        auto offset = it->contents.find(tofind);
        cout << "Found bytes at offset: " << utils::to_hex(it->address + offset) << endl << endl;
    }

    return 0;
}

void bail(string message) {
    cout << message << endl;
    exit(1);
}
