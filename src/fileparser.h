#ifndef FileParser_H
#define FileParser_H

#include <fstream>
#include <string>

#include "binaryfile.h"
#include "results/result.h"
#include "failurereasons.h"

using namespace std;

class FileParser {
    private:
        static Result<BinaryFile, ParseFailure> createProgramHeaders(fstream &fd, BinaryFile &data);
        static Result<BinaryFile, ParseFailure> createSectionHeaders(fstream &fd, BinaryFile &data);

    public:
        static Result<BinaryFile, ParseFailure> Create(string filename);
};

#endif
