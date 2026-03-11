#ifndef OO1_TRUNCATE_H
#define OO1_TRUNCATE_H

#include "FileCmds.h"

class Truncate : public FileCmds{
public:
    void execute(Writer* w) override;
};


#endif //OO1_TRUNCATE_H