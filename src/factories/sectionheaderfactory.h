#ifndef SectionHeaderFactory_H
#define SectionHeaderFactory_H

#include <fstream>
#include <vector>

#include "headers/elfheader.h"
#include "headers/sectionheader.h"
#include "results/result.h"
#include "failurereasons.h"
#include "utils.h"

using namespace std;

class SectionHeaderFactory {
    private:
        static bool isFileOk(fstream &fd);
        static SectionHeader createSingle(fstream &fd, BITNESS bitness, ENDIANESS endianess);
        static SectionHeader deserialize(fstream &fd, int wordSize, ENDIANESS endianess);
        static string getContents(fstream &fd, SectionHeader header);

    public:
        static Result<vector<SectionHeader>, ParseFailure> Create(fstream &fd, ElfHeader elf);
};

#endif
