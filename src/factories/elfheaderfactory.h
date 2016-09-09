#ifndef ElfHeaderFactory_H
#define ElfHeaderFactory_H

#include <fstream>
#include <string>

#include "headers/elfheader.h"
#include "results/result.h"
#include "failurereasons.h"
#include "utils.h"

using namespace std;

class ElfHeaderFactory {
    private:
        static string getIdentity(fstream &fd);
        static bool magicBytesOk(string identity);
        static void setBitness(ElfHeader &elf);
        static void setEndianess(ElfHeader &elf);
        static unsigned int getHalf(fstream &fd, BITNESS bitness, ENDIANESS endianess);
        static unsigned long getWord(fstream &fd, BITNESS bitness, ENDIANESS endianess);

    public:
        static Result<ElfHeader, ParseFailure> Create(fstream &fd);
};

#endif
