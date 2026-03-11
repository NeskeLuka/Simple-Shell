#ifndef OO1_WRITER_H
#define OO1_WRITER_H

#include <fstream>
#include <iosfwd>
#include <string>

class Writer {
public:
    virtual ~Writer();

    explicit Writer(std::ostream *outStream = nullptr) : mOutStream(outStream) {}

    virtual void write(const std::string &s);

    virtual void setPrompt(const std::string&  s);

    virtual void close(){}
protected:
    std::ostream *mOutStream;

    std::string flag;
};

inline Writer::~Writer() {
    delete mOutStream;
}

inline void Writer::write(const std::string &s) {
    (*mOutStream) << s;
}

inline void Writer::setPrompt(const std::string& s) {
    flag = s;
}
#endif //OO1_WRITER_H
