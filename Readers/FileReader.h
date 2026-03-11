#ifndef OO1_FILEREADER_H
#define OO1_FILEREADER_H

#include "fstream"
#include "Reader.h"

class FileReader : public Reader {
public:
    explicit FileReader(const std::string &filename);

    ~FileReader() override;
};

inline FileReader::FileReader(const std::string &filename) : Reader(new std::ifstream(filename)) {
    if (const auto fileStream = dynamic_cast<std::ifstream *>(mInStream); !fileStream->is_open()) {
        delete mInStream;
        mInStream = nullptr;
    }
}

inline FileReader::~FileReader() {
    if (mInStream != nullptr) {
        if (const auto fileStream = dynamic_cast<std::ifstream *>(mInStream); fileStream->is_open()) {
            fileStream->close();
        }
        delete mInStream;
        mInStream = nullptr;
    }
}


#endif //OO1_FILEREADER_H
