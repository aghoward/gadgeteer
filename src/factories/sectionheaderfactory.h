#pragma once

#include <fstream>
#include <memory>

#include "files/filereader.h"
#include "headers/elfheader.h"
#include "headers/sectionheader.h"
#include "results/result.h"
#include "failurereasons.h"

class SectionHeaderFactory {
    private:
        std::shared_ptr<FileReader> m_fileReader;

        bool isFileOk(fstream &fd);
        std::shared_ptr<SectionHeader> createSingle(BITNESS bitness, ENDIANESS endianess);
        std::shared_ptr<SectionHeader> deserialize(int wordSize, ENDIANESS endianess);
        string getName(std::shared_ptr<SectionHeader> header, unsigned long offset);
        string getContents(std::shared_ptr<SectionHeader> header);

    public:
        SectionHeaderFactory() = delete;
        SectionHeaderFactory(std::shared_ptr<FileReader> fileReader) : m_fileReader(fileReader) {};

        Result<std::vector<std::shared_ptr<SectionHeader>>, ParseFailure> Create(std::shared_ptr<ElfHeader> elf);
};
