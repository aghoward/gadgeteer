#pragma once

#include <fstream>
#include <string>

class FileReader {
    private:
        std::fstream m_fd;

    public:
        FileReader(std::string filename) : m_fd(filename, std::ios_base::in | std::ios_base::binary) 
        {
            if (!m_fd.is_open())
                throw std::runtime_error("Unable to open file: " + filename);
        };
        FileReader() = delete;

        FileReader(const FileReader &) = delete;
        FileReader & operator=(const FileReader &) = delete;

        FileReader(FileReader &&) = default;
        FileReader & operator=(FileReader &&) = default;

        ~FileReader() {
            if (m_fd.is_open())
                m_fd.close();
        }

        bool IsOk() const;
        char ReadByte();
        unsigned long ReadBytes(size_t count, ENDIANESS endianess);
        std::string ReadString();
        void Seek(size_t position);
};
