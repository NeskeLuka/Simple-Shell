#include "Reader.h"
#include <iostream>

using namespace std;

std::string Reader::readLine() const {
    string line;
    getline(*mInStream, line);
    //getline reads input until it reaches first '\n' or EOF
    if (!mInStream->eof())
        line.push_back('\n');
    // if line is longer than 512 chars we will use first 512
    if (line.length() > 512) {
        line = line.substr(0, 512);
    }
    return line;
}

vector<std::string> Reader::readLines() {
    vector<string> lines;
    string line;
    while (!isEOF()) {
        lines.push_back(readLine());
    }
    mInStream->clear();
    return lines;
}

bool Reader::isEOF() const {
    return mInStream->eof();
}

void Reader::clear() const {
    mInStream->clear();
}

std::istream *Reader::getInstream() const {
    return mInStream;
}

bool Reader::isPipe() {
    return false;
}
