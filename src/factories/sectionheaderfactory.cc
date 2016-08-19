#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include "../headers/utils.h"

#include "../headers/elfheader.h"
#include "../headers/sectionheader.h"
#include "sectionheaderfactory.h"

using namespace std;
using namespace utils;

string getName(fstream &fd, SectionHeader strtab, unsigned long offset) {
    fd.seekg(strtab.file_offset + offset);
    return readString(fd);
}

vector<SectionHeader> SectionHeaderFactory::Create(fstream &fd, ElfHeader elf) {
    auto headers = vector<SectionHeader>();

    fd.seekg(elf.section_offset);

    for(auto i=0; i<elf.section_entry_count; i++) {
        auto offset = elf.section_offset + (i * elf.section_entry_size);
        auto header = SectionHeader(fd, elf.bitness, elf.endianess);
        headers.push_back(header);
    }

    auto strtab = headers.at(elf.section_name_index);
    for (auto it = headers.begin(); it != headers.end(); it++) {
        it->name = getName(fd, strtab, it->name_offset);
        it->contents = it->getContents(fd);
    }

    return headers;
}
