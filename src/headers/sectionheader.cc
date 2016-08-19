#include <string>
#include <fstream>

#include "sectionheader.h"
#include "utils.h"

#include <iostream>

using namespace std;
using namespace utils;

SectionHeader::SectionHeader(fstream &fd, BITNESS bitness, ENDIANESS endianess) {
    switch(bitness) {
        case BITNESS_32:
            deserialize(fd, 4, endianess);
            break;
        case BITNESS_64:
            deserialize(fd, 8, endianess);
            break;
    }
}

void SectionHeader::deserialize(fstream &fd, int wordSize, ENDIANESS endianess) {
    this->name_offset = getBytes(fd, 4, endianess);
    this->type = getBytes(fd, 4, endianess);
    this->flags = getBytes(fd, wordSize, endianess);
    this->address = getBytes(fd, wordSize, endianess);
    this->file_offset = getBytes(fd, wordSize, endianess);
    this->size = getBytes(fd, wordSize, endianess);
    this->link = getBytes(fd, 4, endianess);
    this->info = getBytes(fd, 4, endianess);
    this->address_alignment = getBytes(fd, wordSize, endianess);
    this->entity_size = getBytes(fd, wordSize, endianess);
}

string SectionHeader::toString() {
    string ret;

    ret += string("Section: ") + this->name + string("\n");
    ret += string("Type: ") + this->getTypeName() + string("\n");
    ret += string("Flags: ") + this->getFlagString() + string("\n");
    ret += string("Address: ") + to_hex(this->address) + string("\n");
    ret += string("File Offset: ") + to_hex(this->file_offset) + string("\n");
    ret += string("Size: ") + to_hex(this->size) + string("\n");
    ret += string("Link Index: ") + to_string(this->link) + string("\n");
    ret += string("Info: ") + to_string(this->info) + string("\n");
    ret += string("Address Alignment: ") + to_hex(this->address_alignment) + string("\n");
    ret += string("Entity Size: ") + to_string(this->entity_size) + ("\n");

    return ret;
}

string SectionHeader::getTypeName() {
    switch(this->type) {
        case SECT_NONE:
            return string("null");
            break;
        case SECT_PROGRAM:
            return string("program data");
            break;
        case SECT_SYMBOL_TABLE:
            return string("symbol table");
            break;
        case SECT_STRING_TABLE:
            return string("string table");
            break;
        default:
            return to_hex(this->type);
    }
}

string SectionHeader::getFlagString() {
    string ret;
    if (this->flags & SECT_WRITE)
        ret += "W";
    if (this->flags & SECT_ALLOCATE)
        ret += "A";
    if (this->flags & SECT_EXECUTE)
        ret += "X";
    if (this->flags & SECT_PROCESSOR)
        ret += "P";
    return ret;
}

string SectionHeader::getContents(fstream &fd) {
    if (this->type == SECT_NONE || this->type == SECT_NOBITS)
        return string();

    fd.seekg(this->file_offset);
    char buf[this->size + 1];

    fd.get(buf, this->size);
    return string(buf);
}
