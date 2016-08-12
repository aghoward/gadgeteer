#include <string>
#include <fstream>

#include "utils.h"
#include "programheader.h"

using namespace std;
using namespace utils;

void ProgramHeader::deserialize32(fstream &fd, ENDIANESS endianess) {
    this->type = (PROGRAM_TYPE)getBytes(fd, 4, endianess);
    this->offset = getBytes(fd, 4, endianess);
    this->virtual_address = getBytes(fd, 4, endianess);
    this->physical_address = getBytes(fd, 4, endianess);
    this->file_size = getBytes(fd, 4, endianess);
    this->memory_size = getBytes(fd, 4, endianess);
    this->flags = getBytes(fd, 4, endianess);
    this->alignment = getBytes(fd, 4, endianess);
}

void ProgramHeader::deserialize64(fstream &fd, ENDIANESS endianess) {
    this->type = (PROGRAM_TYPE)getBytes(fd, 4, endianess);
    this->flags = getBytes(fd, 4, endianess);
    this->offset = getBytes(fd, 4, endianess);
    this->virtual_address = getBytes(fd, 4, endianess);
    this->physical_address = getBytes(fd, 4, endianess);
    this->file_size = getBytes(fd, 4, endianess);
    this->memory_size = getBytes(fd, 4, endianess);
    this->alignment = getBytes(fd, 4, endianess);
}

ProgramHeader::ProgramHeader(fstream &fd, BITNESS bitness, ENDIANESS endianess) {
    switch(bitness) {
        case BITNESS_32:
            deserialize32(fd, endianess);
            break;
        case BITNESS_64:
            deserialize64(fd, endianess);
            break;
    }
}

string ProgramHeader::toString() {
    auto ret = string();

    ret += string("Type: " + to_hex(type) + "\n");
    ret += string("Offset: " + to_hex(offset) + "\n");
    ret += string("Virtual Address: " + to_hex(virtual_address) + "\n");
    ret += string("Physical Address: " + to_hex(physical_address) + "\n");
    ret += string("Size on Disk: " + to_string(file_size) + "\n");
    ret += string("Size in Memory: " + to_string(memory_size) + "\n");
    ret += string("Flags: " + to_string(flags) + "\n");
    ret += string("Alignment: " + to_hex(alignment) + "\n");

    return ret;
}
