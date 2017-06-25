#include <fstream>
#include <iostream>
#include <memory>

#include "bitness.h"
#include "endianess.h"
#include "elfheaderfactory.h"
#include "files/filereader.h"
#include "headers/elfheader.h"
#include "results/result.h"
#include "results/resultfactory.h"
#include "failurereasons.h"

Result<std::shared_ptr<ElfHeader>, ParseFailure> ElfHeaderFactory::Create() {
    m_fileReader->Seek(0);
    if (!m_fileReader->IsOk())
        return ResultFactory::CreateFailure<std::shared_ptr<ElfHeader>>(FileReadError);

    auto elf = std::make_shared<ElfHeader>();

    elf->ident = m_fileReader->ReadString(IDENT_CHARS);
    if (!magicBytesOk(elf->ident))
        return ResultFactory::CreateFailure<std::shared_ptr<ElfHeader>>(InvalidFileFormat);

    setBitness(elf);
    setEndianess(elf);

    elf->type = m_fileReader->ReadBytes(2, elf->endianess);
    elf->machine = m_fileReader->ReadBytes(2, elf->endianess);
    elf->version = m_fileReader->ReadBytes(4, elf->endianess);
    elf->entry = getWord(elf->bitness, elf->endianess);
    elf->program_offset = getWord(elf->bitness, elf->endianess);
    elf->section_offset = getWord(elf->bitness, elf->endianess);
    elf->flags = m_fileReader->ReadBytes(4, elf->endianess);
    elf->program_size = m_fileReader->ReadBytes(2, elf->endianess);
    elf->program_entry_size = m_fileReader->ReadBytes(2, elf->endianess);
    elf->program_entry_count = m_fileReader->ReadBytes(2, elf->endianess);
    elf->section_entry_size = m_fileReader->ReadBytes(2, elf->endianess);
    elf->section_entry_count = m_fileReader->ReadBytes(2, elf->endianess);
    elf->section_name_index = m_fileReader->ReadBytes(2, elf->endianess);

    return ResultFactory::CreateSuccess<std::shared_ptr<ElfHeader>, ParseFailure>(elf);
}

bool ElfHeaderFactory::magicBytesOk(string identity) {
    return identity.find(string("\x7F") + string("ELF")) == 0;
}

void ElfHeaderFactory::setBitness(std::shared_ptr<ElfHeader> elf) {
    auto num = static_cast<int>(elf->ident[4]);
    elf->bitness = static_cast<BITNESS>(num);
}

void ElfHeaderFactory::setEndianess(std::shared_ptr<ElfHeader> elf) {
    auto num = static_cast<int>(elf->ident[5]);
    elf->endianess = static_cast<ENDIANESS>(num);
}

unsigned int ElfHeaderFactory::getHalf(BITNESS bitness, ENDIANESS endianess) {
    auto half = (bitness == BITNESS_32) ? 2 : 4;
    return m_fileReader->ReadBytes(half, endianess);
}

unsigned long ElfHeaderFactory::getWord(BITNESS bitness, ENDIANESS endianess) {
    auto word = (bitness == BITNESS_32) ? 4 : 8;
    return m_fileReader->ReadBytes(word, endianess);
}

