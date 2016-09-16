#ifndef ProgramHeaderFactory_H
#define ProgramHeaderFactory_H

#include <fstream>

#include "qvector.h"
#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "results/result.h"
#include "failurereasons.h"
#include "utils.h"

using namespace std;

class ProgramHeaderFactory {
    private:
        static ProgramHeader createSingle(fstream &fd, BITNESS bitness, ENDIANESS endianess);
        static ProgramHeader deserialize32(fstream &fd, ENDIANESS endianess);
        static ProgramHeader deserialize64(fstream &fd, ENDIANESS endianess);

    public:
        static Result<qvector<ProgramHeader>, ParseFailure> Create(fstream &fd, ElfHeader elf);
};

#endif
