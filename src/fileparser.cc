#include <fstream>
#include <string>
#include <iostream>

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

    BinaryFile data;

    auto elfHeaderResult = ElfHeaderFactory::Create(fd);
    auto result = elfHeaderResult.Match<Result<BinaryFile, ParseFailure>>(
        [&fd, &data] (ElfHeader header) { data.elf_header = header; return createProgramHeaders(fd, data); },
        [] (ParseFailure failure) { return ResultFactory::CreateFailure<BinaryFile>(failure); }
    );

    fd.close();
    return result;
}

Result<BinaryFile, ParseFailure> FileParser::createProgramHeaders(fstream &fd, BinaryFile &returnData) {
    cout << returnData.elf_header.toString() << endl;
    auto parseResult = ProgramHeaderFactory::Create(fd, returnData.elf_header);

    return parseResult.Match<Result<BinaryFile, ParseFailure>>(
        [&fd, &returnData] (vector<ProgramHeader> headers) { returnData.program_headers = headers; return createSectionHeaders(fd, returnData); },
        [] (ParseFailure failure) { return ResultFactory::CreateFailure<BinaryFile>(failure); }
    );
}

Result<BinaryFile, ParseFailure> FileParser::createSectionHeaders(fstream &fd, BinaryFile &returnData) {
    auto parseResult = SectionHeaderFactory::Create(fd, returnData.elf_header);

    return parseResult.Match<Result<BinaryFile, ParseFailure>>(
        [&returnData] (vector<SectionHeader> headers) { returnData.section_headers = headers; return ResultFactory::CreateSuccess<BinaryFile, ParseFailure>(returnData); },
        [] (ParseFailure failure) { return ResultFactory::CreateFailure<BinaryFile>(failure); }
    );
}
