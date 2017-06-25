#include <fstream>
#include <memory>

#include "bitness.h"
#include "endianess.h"
#include "programheaderfactory.h"
#include "headers/programheader.h"
#include "headers/elfheader.h"
#include "results/result.h"
#include "results/resultfactory.h"
#include "failurereasons.h"

Result<std::vector<std::shared_ptr<ProgramHeader>>, ParseFailure> ProgramHeaderFactory::Create(std::shared_ptr<ElfHeader> elf) {
    auto headers = std::vector<std::shared_ptr<ProgramHeader>>();

    for (auto i = 0; i < elf->program_entry_count; i++) {
        auto offset = elf->program_offset + (i * elf->program_entry_size);
        m_fileReader->Seek(offset);
        if (!m_fileReader->IsOk())
            return ResultFactory::CreateFailure<std::vector<std::shared_ptr<ProgramHeader>>>(FileReadError);

        auto header = createSingle(elf->bitness, elf->endianess);
        headers.push_back(header);
    }

    return ResultFactory::CreateSuccess<std::vector<std::shared_ptr<ProgramHeader>>, ParseFailure>(headers);
}

std::shared_ptr<ProgramHeader> ProgramHeaderFactory::deserialize32(ENDIANESS endianess) {
    auto header = std::make_shared<ProgramHeader>();
    
    header->type = static_cast<PROGRAM_TYPE>(m_fileReader->ReadBytes(4, endianess));
    header->offset = m_fileReader->ReadBytes(4, endianess);
    header->virtual_address = m_fileReader->ReadBytes(4, endianess);
    header->physical_address = m_fileReader->ReadBytes(4, endianess);
    header->file_size = m_fileReader->ReadBytes(4, endianess);
    header->memory_size = m_fileReader->ReadBytes(4, endianess);
    header->flags = m_fileReader->ReadBytes(4, endianess);
    header->alignment = m_fileReader->ReadBytes(4, endianess);

    return header;
}

std::shared_ptr<ProgramHeader> ProgramHeaderFactory::deserialize64(ENDIANESS endianess) {
    auto header = std::make_shared<ProgramHeader>();

    header->type = static_cast<PROGRAM_TYPE>(m_fileReader->ReadBytes(4, endianess));
    header->flags = m_fileReader->ReadBytes(4, endianess);
    header->offset = m_fileReader->ReadBytes(4, endianess);
    header->virtual_address = m_fileReader->ReadBytes(4, endianess);
    header->physical_address = m_fileReader->ReadBytes(4, endianess);
    header->file_size = m_fileReader->ReadBytes(4, endianess);
    header->memory_size = m_fileReader->ReadBytes(4, endianess);
    header->alignment = m_fileReader->ReadBytes(4, endianess);

    return header;
}

std::shared_ptr<ProgramHeader> ProgramHeaderFactory::createSingle(BITNESS bitness, ENDIANESS endianess) {
    return (bitness == BITNESS_32) ? deserialize32(endianess) : deserialize64(endianess);
}
