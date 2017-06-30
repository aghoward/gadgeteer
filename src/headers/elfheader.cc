#include <iostream>
#include <fstream>
#include <string>

#include "bitness.h"
#include "endianess.h"
#include "elfheader.h"

#include "utils.h"
using namespace utils;

using namespace std;

string ElfHeader::toString() {
    auto ret = string();
    ret += string("Identity: ") + ident + string("\n");
    ret += string("Bitness: ") + this->getBitness() + string("\n");
    ret += string("Endianess: ") + this->getEndianess() + string("\n");
    ret += string("Type: " + to_string(type) + "\n");
    ret += string("Machine: " + to_string(machine) + "\n");
    ret += string("Version: " + to_string(version) + "\n");
    ret += string("Entry Point: " + to_hex(entry) + "\n");
    ret += string("Program Offset: " + to_hex(program_offset) + "\n");
    ret += string("Section Offset: " + to_hex(section_offset) + "\n");
    ret += string("Flags: " + to_string(flags) + "\n");
    ret += string("Program Size: " + to_string(program_size) + "\n");
    ret += string("Program Entry Size: " + to_string(program_entry_size) + "\n");
    ret += string("Program Entry Count: " + to_string(program_entry_count) + "\n");
    ret += string("Section Entry Size: " + to_string(section_entry_size) + "\n");
    ret += string("Section Entry Count: " + to_string(section_entry_count) + "\n");
    ret += string("Section Name Index: " + to_hex(section_name_index) + "\n");
    return ret;
}

string ElfHeader::getBitness() {
    switch(this->bitness) {
        case BITNESS_32:
            return string("32-bit");
            break;
        case BITNESS_64:
            return string("64-bit");
            break;
        default:
            return string();
    }
}

string ElfHeader::getEndianess() {
    switch(this->endianess){
        case ENDIAN_LITTLE:
            return string("little");
            break;
        case ENDIAN_BIG:
            return string("big");
            break;
        default:
            return string();
    }
}

