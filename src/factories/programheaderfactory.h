#pragma once

#include <fstream>
#include <memory>

#include "bitness.h"
#include "endianess.h"
#include "files/filereader.h"
#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "results/result.h"
#include "failurereasons.h"

class ProgramHeaderFactory {
    private:
        std::shared_ptr<FileReader> m_fileReader;

        std::shared_ptr<ProgramHeader> createSingle(BITNESS bitness, ENDIANESS endianess);
        std::shared_ptr<ProgramHeader> deserialize32(ENDIANESS endianess);
        std::shared_ptr<ProgramHeader> deserialize64(ENDIANESS endianess);

    public:
        ProgramHeaderFactory() = delete;
        ProgramHeaderFactory(std::shared_ptr<FileReader> fileReader) : m_fileReader(fileReader) {};

        Result<std::vector<std::shared_ptr<ProgramHeader>>, ParseFailure> Create(std::shared_ptr<ElfHeader> elf);
};
