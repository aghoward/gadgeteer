#ifndef ProgramHeaderFactory_H
#define ProgramHeaderFactory_H

#include <fstream>
#include <memory>

#include "qvector.h"
#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "results/result.h"
#include "failurereasons.h"
#include "utils.h"

using namespace std;

class ProgramHeaderFactory {
    private:
        static shared_ptr<ProgramHeader> createSingle(fstream &fd, BITNESS bitness, ENDIANESS endianess);
        static shared_ptr<ProgramHeader> deserialize32(fstream &fd, ENDIANESS endianess);
        static shared_ptr<ProgramHeader> deserialize64(fstream &fd, ENDIANESS endianess);

    public:
        static Result<qvector<shared_ptr<ProgramHeader>>, ParseFailure> Create(fstream &fd, shared_ptr<ElfHeader> elf);
};

#endif
