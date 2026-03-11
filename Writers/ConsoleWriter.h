#ifndef OO1_CONSOLEWRITER_H
#define OO1_CONSOLEWRITER_H

#include <algorithm>
#include <iostream>
#include "Writer.h"

class ConsoleWriter : public Writer {
public:
    ConsoleWriter() : Writer(&std::cout) {}

    void write(const std::string &s) override;
protected:
     [[nodiscard]] bool isAllSpace(const std::string& s) const;
};
inline void ConsoleWriter::write(const std::string &s) {
    Writer::write(s);
    if (!isAllSpace(s) && s.find('\n')==std::string::npos) {
        std::cout << std::endl;
    }
}

inline bool ConsoleWriter::isAllSpace(const std::string& s) const {
    if (s==flag+" ")
        return true;
    return std::find_if_not(s.begin(), s.end(), [](const unsigned char c) { return std::isspace(c); }) == s.end();
}
#endif //OO1_CONSOLEWRITER_H