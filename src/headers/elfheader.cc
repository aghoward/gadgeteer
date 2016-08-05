#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"
#include "elfheader.h"

using namespace std;
using namespace utils;

ElfHeader::ElfHeader(fstream& fd) {
    fd.seekg(0, ios_base::beg);

    this->ident = getIdentity(fd);

    this->setBitness();
    this->setEndianess();

    this->type = getBytes(fd, 2, this->endianess);
    this->machine = getBytes(fd, 2, this->endianess);
    this->version = getBytes(fd, 4, this->endianess);
    this->entry = getWord(fd);
    this->program_offset = getWord(fd);
    this->section_offset = getWord(fd);
    this->flags = getBytes(fd, 4, this->endianess);
    this->program_size = getBytes(fd, 2, this->endianess);
    this->program_entry_size = getBytes(fd, 2, this->endianess);
    this->program_entry_count = getBytes(fd, 2, this->endianess);
    this->section_size = getBytes(fd, 2, this->endianess);
    this->section_entry_size = getBytes(fd, 2, this->endianess);
    this->section_entry_count = getBytes(fd, 2, this->endianess);
    this->section_name_index = getBytes(fd, 2, this->endianess);
}

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
    ret += string("Section Size: " + to_string(section_size) + "\n");
    ret += string("Section Entry Size: " + to_string(section_entry_size) + "\n");
    ret += string("Section Entry Count: " + to_string(section_entry_count) + "\n");
    ret += string("Section Name Index: " + to_hex(section_name_index) + "\n");
    return ret;
}

string ElfHeader::getIdentity(fstream& fd) {
    char data[IDENT_CHARS];
    fd.get(data, IDENT_CHARS);
    fd.seekg(IDENT_CHARS);
    return string(data);
}

void ElfHeader::setBitness() {
    auto num = (int)((char)this->ident[4]);
    this->bitness = (BITNESS)num;
}

void ElfHeader::setEndianess() {
    auto num = (int)((char)this->ident[5]);
    this->endianess = (ENDIANESS)num;
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

unsigned int ElfHeader::getHalf(fstream& fd) {
    auto half = (this->bitness == BITNESS_32) ? 2 : 4;
    return getBytes(fd, half, this->endianess);
}

unsigned long ElfHeader::getWord(fstream& fd) {
    auto word = (this->bitness == BITNESS_32) ? 4 : 8;
    return getBytes(fd, word, this->endianess);
}

