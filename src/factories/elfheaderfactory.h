#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "bitness.h"
#include "endianess.h"
#include "files/filereader.h"
#include "headers/elfheader.h"
#include "results/result.h"
#include "failurereasons.h"

class ElfHeaderFactory {
    private:
        std::shared_ptr<FileReader> m_fileReader;

        bool magicBytesOk(string identity);
        void setBitness(std::shared_ptr<ElfHeader> elf);
        void setEndianess(std::shared_ptr<ElfHeader> elf);
        unsigned int getHalf(BITNESS bitness, ENDIANESS endianess);
        unsigned long getWord(BITNESS bitness, ENDIANESS endianess);

    public:
        ElfHeaderFactory() = delete;
        ElfHeaderFactory(std::shared_ptr<FileReader> fileReader) : m_fileReader(fileReader) {};

        Result<std::shared_ptr<ElfHeader>, ParseFailure> Create();
};
