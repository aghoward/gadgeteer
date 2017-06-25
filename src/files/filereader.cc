#include <fstream>
#include <string>

#include "endianess.h"
#include "files/filereader.h"

bool FileReader::IsOk() const {
    return !(m_fd.bad() || m_fd.fail());
}

char FileReader::ReadByte() {
    return static_cast<char>(m_fd.get() & 0xFF);
}

unsigned long FileReader::ReadBytes(size_t count, ENDIANESS endianess) {
        unsigned long ret = 0;
        auto byteSize = 8;

        for (int i = 0; i < count; i++) {
            auto c = static_cast<char>(m_fd.get());
            auto curr = static_cast<unsigned short>(c) & 0x00FF;

            auto shift = (endianess == ENDIAN_LITTLE) ? (i * byteSize) : ((count - i) * byteSize);

            ret += curr << shift;
        }

        return ret;
}

std::string FileReader::ReadString() {
    auto ret = std::string();
    char c = static_cast<char>(m_fd.get());

    while (c != 0x00) {
        ret += c;
        c = static_cast<char>(m_fd.get());
    }

    return ret;
}

std::string FileReader::ReadString(size_t length) {
    char cstr[length];
    m_fd.get(cstr, length);
    Seek(length);
    return std::string(cstr);
};

void FileReader::Seek(size_t position) {
    m_fd.seekg(position);
}
