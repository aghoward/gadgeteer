#include <string>
#include <fstream>

#include "sectionheader.h"
#include "utils.h"

#include <iostream>

using namespace std;
using namespace utils;

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
