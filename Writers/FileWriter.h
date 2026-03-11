#ifndef OO1_FILEWRITER_H
#define OO1_FILEWRITER_H

#include <fstream>
#include "Writer.h"
#include <string>

class FileWriter : public Writer {
public:
    explicit FileWriter(const std::string &fileName, const std::ios::openmode mode = std::ios::out)
        : Writer(new std::ofstream(fileName, mode)) {
    }
    ~FileWriter() override;

    void close() override;
};
inline FileWriter::~FileWriter() {
    if (mOutStream != nullptr) {
        if (const auto fileStream = dynamic_cast<std::ofstream *>(mOutStream); fileStream && fileStream->is_open()) {
            fileStream->close();
        }
        delete mOutStream;
        mOutStream = nullptr;
    }
}

inline void FileWriter::close() {
    if (mOutStream != nullptr) {
        if (const auto fileStream = dynamic_cast<std::ofstream *>(mOutStream); fileStream && fileStream->is_open()) {
            fileStream->close();
        }
    }
}
#endif //OO1_FILEWRITER_H
