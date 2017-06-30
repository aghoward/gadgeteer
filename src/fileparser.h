#pragma once

#include <functional>
#include <memory>
#include <string>

#include "binaryfile.h"
#include "factories/elfheaderfactory.h"
#include "factories/programheaderfactory.h"
#include "factories/sectionheaderfactory.h"
#include "files/filereader.h"
#include "results/result.h"
#include "failurereasons.h"

class FileParser {
    private:
        std::function<std::shared_ptr<FileReader> (std::string)> m_fileReaderFactory;
        std::function<std::unique_ptr<ElfHeaderFactory> (std::shared_ptr<FileReader>)> m_elfHeaderFactoryFactory;
        std::function<std::unique_ptr<ProgramHeaderFactory> (std::shared_ptr<FileReader>)> m_programHeaderFactoryFactory;
        std::function<std::unique_ptr<SectionHeaderFactory> (std::shared_ptr<FileReader>)> m_sectionHeaderFactoryFactory;

        Result<std::shared_ptr<BinaryFile>, ParseFailure> createElfHeader(std::shared_ptr<FileReader> fd, std::shared_ptr<BinaryFile> data);
        Result<std::shared_ptr<BinaryFile>, ParseFailure> createProgramHeaders(std::shared_ptr<FileReader> fd, std::shared_ptr<BinaryFile> data);
        Result<std::shared_ptr<BinaryFile>, ParseFailure> createSectionHeaders(std::shared_ptr<FileReader> fd, std::shared_ptr<BinaryFile> data);

    public:
        FileParser(
            std::function<std::shared_ptr<FileReader> (std::string)> frf,
            std::function<std::unique_ptr<ElfHeaderFactory> (std::shared_ptr<FileReader>)> ehff,
            std::function<std::unique_ptr<ProgramHeaderFactory> (std::shared_ptr<FileReader>)> phff,
            std::function<std::unique_ptr<SectionHeaderFactory> (std::shared_ptr<FileReader>)> shff)
            : 
            m_fileReaderFactory(frf),
            m_elfHeaderFactoryFactory(ehff),
            m_programHeaderFactoryFactory(phff),
            m_sectionHeaderFactoryFactory(shff) {};
;

        Result<std::shared_ptr<BinaryFile>, ParseFailure> Create(std::string filename);
};
