#include <fstream>
#include <iostream>
#include <memory>

#include "elfheaderfactory.h"
#include "headers/elfheader.h"
#include "results/result.h"
#include "results/resultfactory.h"
#include "utils.h"
#include "failurereasons.h"

using namespace utils;

Result<shared_ptr<ElfHeader>, ParseFailure> ElfHeaderFactory::Create(fstream& fd) {
    fd.seekg(0, ios_base::beg);
    if (fd.fail() || fd.bad())
        return ResultFactory::CreateFailure<shared_ptr<ElfHeader>>(FileReadError);

    auto elf = shared_ptr<ElfHeader>(new ElfHeader());

    elf->ident = getIdentity(fd);
    if (!magicBytesOk(elf->ident)){
        return ResultFactory::CreateFailure<shared_ptr<ElfHeader>>(InvalidFileFormat);
    }

    setBitness(elf);
    setEndianess(elf);

    elf->type = getBytes(fd, 2, elf->endianess);
    elf->machine = getBytes(fd, 2, elf->endianess);
    elf->version = getBytes(fd, 4, elf->endianess);
    elf->entry = getWord(fd, elf->bitness, elf->endianess);
    elf->program_offset = getWord(fd, elf->bitness, elf->endianess);
    elf->section_offset = getWord(fd, elf->bitness, elf->endianess);
    elf->flags = getBytes(fd, 4, elf->endianess);
    elf->program_size = getBytes(fd, 2, elf->endianess);
    elf->program_entry_size = getBytes(fd, 2, elf->endianess);
    elf->program_entry_count = getBytes(fd, 2, elf->endianess);
    elf->section_entry_size = getBytes(fd, 2, elf->endianess);
    elf->section_entry_count = getBytes(fd, 2, elf->endianess);
    elf->section_name_index = getBytes(fd, 2, elf->endianess);

    return ResultFactory::CreateSuccess<shared_ptr<ElfHeader>, ParseFailure>(elf);
}


string ElfHeaderFactory::getIdentity(fstream& fd) {
    char data[IDENT_CHARS];
    fd.get(data, IDENT_CHARS);
    fd.seekg(IDENT_CHARS);
    return string(data);
}

bool ElfHeaderFactory::magicBytesOk(string identity) {
    return identity.find(string("\x7F") + string("ELF")) == 0;
}

void ElfHeaderFactory::setBitness(shared_ptr<ElfHeader> elf) {
    auto num = (int)((char)elf->ident[4]);
    elf->bitness = (BITNESS)num;
}

void ElfHeaderFactory::setEndianess(shared_ptr<ElfHeader> elf) {
    auto num = (int)((char)elf->ident[5]);
    elf->endianess = (ENDIANESS)num;
}

unsigned int ElfHeaderFactory::getHalf(fstream& fd, BITNESS bitness, ENDIANESS endianess) {
    auto half = (bitness == BITNESS_32) ? 2 : 4;
    return getBytes(fd, half, endianess);
}

unsigned long ElfHeaderFactory::getWord(fstream& fd, BITNESS bitness, ENDIANESS endianess) {
    auto word = (bitness == BITNESS_32) ? 4 : 8;
    return getBytes(fd, word, endianess);
}

