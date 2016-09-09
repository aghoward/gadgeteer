#include <string>
#include <fstream>

#include "utils.h"
#include "programheader.h"

using namespace std;
using namespace utils;

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
