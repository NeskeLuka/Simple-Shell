#ifndef OO1_READER_H
#define OO1_READER_H

#include <istream>
#include <string>
#include <vector>

class Reader {
public:
    explicit Reader(std::istream *inStream=nullptr) : mInStream(inStream) {}

    virtual ~Reader() = default;

    [[nodiscard]] std::string readLine() const;

    [[nodiscard]] virtual std::vector<std::string> readLines();

    [[nodiscard]] bool isEOF() const;

    void clear() const;

    [[nodiscard]] std::istream *getInstream() const;

    virtual bool isPipe();
protected:
    std::istream *mInStream{};
};
#endif //OO1_READER_H
