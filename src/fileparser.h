#ifndef FileParser_H
#define FileParser_H

#include <fstream>
#include <memory>
#include <string>

#include "binaryfile.h"
#include "results/result.h"
#include "failurereasons.h"

using namespace std;

class FileParser {
    private:
        static Result<shared_ptr<BinaryFile>, ParseFailure> createElfHeader(fstream &fd, shared_ptr<BinaryFile> data);
        static Result<shared_ptr<BinaryFile>, ParseFailure> createProgramHeaders(fstream &fd, shared_ptr<BinaryFile> data);
        static Result<shared_ptr<BinaryFile>, ParseFailure> createSectionHeaders(fstream &fd, shared_ptr<BinaryFile> data);

    public:
        static Result<shared_ptr<BinaryFile>, ParseFailure> Create(string filename);
};

#endif
