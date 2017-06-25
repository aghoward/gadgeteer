#include <fstream>
#include <iostream>
#include <memory>
#include <string>


#include "files/filereader.h"
#include "headers/elfheader.h"
#include "headers/sectionheader.h"
#include "results/result.h"
#include "results/resultfactory.h"
#include "failurereasons.h"
#include "sectionheaderfactory.h"

string SectionHeaderFactory::getName(std::shared_ptr<SectionHeader> strtab, unsigned long offset) {
    m_fileReader->Seek(strtab->file_offset + offset);
    return m_fileReader->ReadString();
}

Result<std::vector<std::shared_ptr<SectionHeader>>, ParseFailure> SectionHeaderFactory::Create(std::shared_ptr<ElfHeader> elf) {
    auto headers = std::vector<std::shared_ptr<SectionHeader>>();

    m_fileReader->Seek(elf->section_offset);
    if (!m_fileReader->IsOk())
        return ResultFactory::CreateFailure<std::vector<std::shared_ptr<SectionHeader>>>(FileReadError);

    for(auto i=0; i<elf->section_entry_count; i++) {
        auto offset = elf->section_offset + (i * elf->section_entry_size);
        auto header = createSingle(elf->bitness, elf->endianess);
        headers.push_back(header);

        if (!m_fileReader->IsOk())
            return ResultFactory::CreateFailure<std::vector<std::shared_ptr<SectionHeader>>>(FileReadError);
    }

    auto strtab = headers.at(elf->section_name_index);
    for (auto it : headers) {
        it->name = getName(strtab, it->name_offset);
        it->contents = getContents(it);

        if (!m_fileReader->IsOk())
            return ResultFactory::CreateFailure<std::vector<std::shared_ptr<SectionHeader>>>(FileReadError);
    }

    return ResultFactory::CreateSuccess<std::vector<std::shared_ptr<SectionHeader>>, ParseFailure>(headers);
}

std::shared_ptr<SectionHeader> SectionHeaderFactory::createSingle(BITNESS bitness, ENDIANESS endianess) {
    return (bitness == BITNESS_32) ? deserialize(4, endianess) : deserialize(8, endianess);
}

std::shared_ptr<SectionHeader> SectionHeaderFactory::deserialize(int wordSize, ENDIANESS endianess) {
    auto header = std::make_shared<SectionHeader>();

    header->name_offset = m_fileReader->ReadBytes(4, endianess);
    header->type = m_fileReader->ReadBytes(4, endianess);
    header->flags = m_fileReader->ReadBytes(wordSize, endianess);
    header->address = m_fileReader->ReadBytes(wordSize, endianess);
    header->file_offset = m_fileReader->ReadBytes(wordSize, endianess);
    header->size = m_fileReader->ReadBytes(wordSize, endianess);
    header->link = m_fileReader->ReadBytes(4, endianess);
    header->info = m_fileReader->ReadBytes(4, endianess);
    header->address_alignment = m_fileReader->ReadBytes(wordSize, endianess);
    header->entity_size = m_fileReader->ReadBytes(wordSize, endianess);

    return header;
}

string SectionHeaderFactory::getContents(std::shared_ptr<SectionHeader> header) {
    if (header->type == SECT_NONE || header->type == SECT_NOBITS)
        return string();

    m_fileReader->Seek(header->file_offset);
    auto output = string();

    for (auto i = 0; i < header->size; i++) {
        output += m_fileReader->ReadByte();
    }

    return output;
}
