#ifndef OO1_CONSOLEREADER_H
#define OO1_CONSOLEREADER_H

#include <iostream>
#include "Reader.h"

class ConsoleReader : public Reader {
public:
    ConsoleReader() : Reader(&std::cin) {
    }
};


#endif //OO1_CONSOLEREADER_H
