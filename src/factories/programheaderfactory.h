#ifndef ProgramHeaderFactory_H
#define ProgramHeaderFactory_H

#include <fstream>
#include <vector>

#include "headers/elfheader.h"
#include "headers/programheader.h"

using namespace std;

class ProgramHeaderFactory {
    public:
        static vector<ProgramHeader> Create(fstream &fd, ElfHeader elf);
};

#endif
