#ifndef OO1_PIPE2_H
#define OO1_PIPE2_H
#include "../Writers/Writer.h"
#include "../Readers/Reader.h"
#include <queue>

class Pipe :public Reader, public Writer{
public:

    void write(const std::string& s) override;

    [[nodiscard]] std::vector<std::string> readLines()  override;

    bool isPipe() override;
private:
    std::queue<std::string> buffer;
};

#endif //OO1_PIPE2_H
