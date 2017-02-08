#include <fstream>
#include <memory>

#include "qvector.h"
#include "programheaderfactory.h"
#include "headers/programheader.h"
#include "headers/elfheader.h"
#include "results/result.h"
#include "results/resultfactory.h"
#include "failurereasons.h"
#include "utils.h"

using namespace std;
using namespace utils;

Result<qvector<shared_ptr<ProgramHeader>>, ParseFailure> ProgramHeaderFactory::Create(fstream &fd, shared_ptr<ElfHeader> elf) {
    auto headers = qvector<shared_ptr<ProgramHeader>>();

    for (auto i = 0; i < elf->program_entry_count; i++) {
        auto offset = elf->program_offset + (i * elf->program_entry_size);
        fd.seekg(offset);
        if (fd.bad() || fd.fail())
            return ResultFactory::CreateFailure<qvector<shared_ptr<ProgramHeader>>>(FileReadError);

        auto header = createSingle(fd, elf->bitness, elf->endianess);
        headers.push_back(header);
    }

    return ResultFactory::CreateSuccess<qvector<shared_ptr<ProgramHeader>>, ParseFailure>(headers);
}

shared_ptr<ProgramHeader> ProgramHeaderFactory::deserialize32(fstream &fd, ENDIANESS endianess) {
    auto header = shared_ptr<ProgramHeader>(new ProgramHeader());
    
    header->type = (PROGRAM_TYPE)getBytes(fd, 4, endianess);
    header->offset = getBytes(fd, 4, endianess);
    header->virtual_address = getBytes(fd, 4, endianess);
    header->physical_address = getBytes(fd, 4, endianess);
    header->file_size = getBytes(fd, 4, endianess);
    header->memory_size = getBytes(fd, 4, endianess);
    header->flags = getBytes(fd, 4, endianess);
    header->alignment = getBytes(fd, 4, endianess);

    return header;
}

shared_ptr<ProgramHeader> ProgramHeaderFactory::deserialize64(fstream &fd, ENDIANESS endianess) {
    auto header = shared_ptr<ProgramHeader>(new ProgramHeader());

    header->type = (PROGRAM_TYPE)getBytes(fd, 4, endianess);
    header->flags = getBytes(fd, 4, endianess);
    header->offset = getBytes(fd, 4, endianess);
    header->virtual_address = getBytes(fd, 4, endianess);
    header->physical_address = getBytes(fd, 4, endianess);
    header->file_size = getBytes(fd, 4, endianess);
    header->memory_size = getBytes(fd, 4, endianess);
    header->alignment = getBytes(fd, 4, endianess);

    return header;
}

shared_ptr<ProgramHeader> ProgramHeaderFactory::createSingle(fstream &fd, BITNESS bitness, ENDIANESS endianess) {
    return (bitness == BITNESS_32) ? deserialize32(fd, endianess) : deserialize64(fd, endianess);
}
