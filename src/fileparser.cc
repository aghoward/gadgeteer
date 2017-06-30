#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "fileparser.h"
#include "binaryfile.h"
#include "factories/elfheaderfactory.h"
#include "factories/programheaderfactory.h"
#include "factories/sectionheaderfactory.h"
#include "results/result.h"
#include "results/resultfactory.h"

Result<std::shared_ptr<BinaryFile>, ParseFailure> FileParser::Create(std::string filename) {
    auto fd = m_fileReaderFactory(filename);
    if (!fd->IsOk())
        return ResultFactory::CreateFailure<std::shared_ptr<BinaryFile>>(FileDoesNotExist);

    auto data = std::make_shared<BinaryFile>();
    auto result = createElfHeader(fd, data);

    return result;
}

Result<std::shared_ptr<BinaryFile>, ParseFailure> FileParser::createElfHeader(shared_ptr<FileReader> fd, std::shared_ptr<BinaryFile> returnData) {
    auto elfHeaderFactory = m_elfHeaderFactoryFactory(fd);
    auto elfHeaderResult = elfHeaderFactory->Create();
    return elfHeaderResult.Match<Result<std::shared_ptr<BinaryFile>, ParseFailure>>(
        [&] (auto header) {
            returnData->elf_header = header;
            return createProgramHeaders(fd, returnData);
        },
        [] (auto failure) { return ResultFactory::CreateFailure<std::shared_ptr<BinaryFile>>(failure); }
    );
}

Result<std::shared_ptr<BinaryFile>, ParseFailure> FileParser::createProgramHeaders(shared_ptr<FileReader> fd, std::shared_ptr<BinaryFile> returnData) {
    auto programHeaderFactory = m_programHeaderFactoryFactory(fd);
    auto parseResult = programHeaderFactory->Create(returnData->elf_header);

    return parseResult.Match<Result<std::shared_ptr<BinaryFile>, ParseFailure>>(
        [&] (auto headers) {
            returnData->program_headers = headers;
            return createSectionHeaders(fd, returnData); 
        },
        [] (auto failure) { return ResultFactory::CreateFailure<std::shared_ptr<BinaryFile>>(failure); }
    );
}

Result<std::shared_ptr<BinaryFile>, ParseFailure> FileParser::createSectionHeaders(std::shared_ptr<FileReader> fd, std::shared_ptr<BinaryFile> returnData) {
    auto sectionHeaderFactory = m_sectionHeaderFactoryFactory(fd);
    auto parseResult = sectionHeaderFactory->Create(returnData->elf_header);

    return parseResult.Match<Result<std::shared_ptr<BinaryFile>, ParseFailure>>(
        [&returnData] (auto headers) { 
            returnData->section_headers = headers;
            return ResultFactory::CreateSuccess<std::shared_ptr<BinaryFile>, ParseFailure>(returnData); 
        },
        [] (auto failure) { return ResultFactory::CreateFailure<std::shared_ptr<BinaryFile>>(failure); }
    );
}
