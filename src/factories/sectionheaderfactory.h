#ifndef SectionHeaderFactory_H
#define SectionHeaderFactory_H

#include <fstream>
#include <vector>

#include "headers/elfheader.h"
#include "headers/sectionheader.h"

using namespace std;

class SectionHeaderFactory {
    public:
        static vector<SectionHeader> Create(fstream &fd, ElfHeader elf);
};

#endif
