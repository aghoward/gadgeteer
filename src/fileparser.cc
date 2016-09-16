#include <fstream>
#include <string>
#include <iostream>

#include "qvector.h"
#include "fileparser.h"
#include "binaryfile.h"
#include "factories/elfheaderfactory.h"
#include "factories/programheaderfactory.h"
#include "factories/sectionheaderfactory.h"
#include "results/result.h"
#include "results/resultfactory.h"

using namespace std;

Result<BinaryFile, ParseFailure> FileParser::Create(string filename) {
    fstream fd(filename, ios::in | ios::binary);
    if (!fd.is_open())
        return ResultFactory::CreateFailure<BinaryFile>(FileDoesNotExist);

    BinaryFile data = BinaryFile();
    auto result = FileParser::createElfHeader(fd, data);

    fd.close();
    return result;
}

Result<BinaryFile, ParseFailure> FileParser::createElfHeader(fstream &fd, BinaryFile &returnData) {
    auto elfHeaderResult = ElfHeaderFactory::Create(fd);
    return elfHeaderResult.Match<Result<BinaryFile, ParseFailure>>(
        [&fd, &returnData] (auto header) {
            returnData.elf_header = header;
            return FileParser::createProgramHeaders(fd, returnData);
        },
        [] (auto failure) { return ResultFactory::CreateFailure<BinaryFile>(failure); }
    );
}

Result<BinaryFile, ParseFailure> FileParser::createProgramHeaders(fstream &fd, BinaryFile &returnData) {
    auto parseResult = ProgramHeaderFactory::Create(fd, returnData.elf_header);

    return parseResult.Match<Result<BinaryFile, ParseFailure>>(
        [&fd, &returnData] (auto headers) {
            returnData.program_headers = headers; 
            return FileParser::createSectionHeaders(fd, returnData); 
        },
        [] (auto failure) { return ResultFactory::CreateFailure<BinaryFile>(failure); }
    );
}

Result<BinaryFile, ParseFailure> FileParser::createSectionHeaders(fstream &fd, BinaryFile &returnData) {
    auto parseResult = SectionHeaderFactory::Create(fd, returnData.elf_header);

    return parseResult.Match<Result<BinaryFile, ParseFailure>>(
        [&returnData] (auto headers) { 
            returnData.section_headers = headers;
            return ResultFactory::CreateSuccess<BinaryFile, ParseFailure>(returnData); 
        },
        [] (auto failure) { return ResultFactory::CreateFailure<BinaryFile>(failure); }
    );
}
