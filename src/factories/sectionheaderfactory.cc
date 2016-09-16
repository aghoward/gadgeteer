#include <string>
#include <fstream>

#include <iostream>

#include "utils.h"
#include "qvector.h"

#include "headers/elfheader.h"
#include "headers/sectionheader.h"
#include "results/result.h"
#include "results/resultfactory.h"
#include "failurereasons.h"
#include "sectionheaderfactory.h"

using namespace std;
using namespace utils;

string getName(fstream &fd, SectionHeader strtab, unsigned long offset) {
    fd.seekg(strtab.file_offset + offset);
    return readString(fd);
}

Result<qvector<SectionHeader>, ParseFailure> SectionHeaderFactory::Create(fstream &fd, ElfHeader elf) {
    auto headers = qvector<SectionHeader>();

    fd.seekg(elf.section_offset);
    if (!isFileOk(fd))
        return ResultFactory::CreateFailure<qvector<SectionHeader>>(FileReadError);

    for(auto i=0; i<elf.section_entry_count; i++) {
        auto offset = elf.section_offset + (i * elf.section_entry_size);
        auto header = createSingle(fd, elf.bitness, elf.endianess);
        headers.push_back(header);

        if (!isFileOk(fd))
            return ResultFactory::CreateFailure<qvector<SectionHeader>>(FileReadError);
    }

    auto strtab = headers.at(elf.section_name_index);
    for (auto it = headers.begin(); it != headers.end(); it++) {
        it->name = getName(fd, strtab, it->name_offset);
        it->contents = getContents(fd, *it);

        if (!isFileOk(fd))
            return ResultFactory::CreateFailure<qvector<SectionHeader>>(FileReadError);
    }

    return ResultFactory::CreateSuccess<qvector<SectionHeader>, ParseFailure>(headers);
}

bool SectionHeaderFactory::isFileOk(fstream &fd) {
    return !fd.bad() && !fd.fail();
}

SectionHeader SectionHeaderFactory::createSingle(fstream &fd, BITNESS bitness, ENDIANESS endianess) {
    return (bitness == BITNESS_32) ? deserialize(fd, 4, endianess) : deserialize(fd, 8, endianess);
}

SectionHeader SectionHeaderFactory::deserialize(fstream &fd, int wordSize, ENDIANESS endianess) {
    SectionHeader header;

    header.name_offset = getBytes(fd, 4, endianess);
    header.type = getBytes(fd, 4, endianess);
    header.flags = getBytes(fd, wordSize, endianess);
    header.address = getBytes(fd, wordSize, endianess);
    header.file_offset = getBytes(fd, wordSize, endianess);
    header.size = getBytes(fd, wordSize, endianess);
    header.link = getBytes(fd, 4, endianess);
    header.info = getBytes(fd, 4, endianess);
    header.address_alignment = getBytes(fd, wordSize, endianess);
    header.entity_size = getBytes(fd, wordSize, endianess);

    return header;
}

string SectionHeaderFactory::getContents(fstream &fd, SectionHeader header) {
    if (header.type == SECT_NONE || header.type == SECT_NOBITS)
        return string();

    fd.seekg(header.file_offset);
    char buf[header.size + 1];

    fd.get(buf, header.size);
    return string(buf);
}
