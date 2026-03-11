#include "Pipe.h"
using namespace std;

void Pipe::write(const std::string &s) {
    buffer.push(s);
}

vector<std::string> Pipe::readLines() {
    vector<string> result;

    if (buffer.empty())
        return result;

    result.push_back(buffer.front());
    buffer.pop();

    return result;
}

bool Pipe::isPipe() {
    return true;
}
