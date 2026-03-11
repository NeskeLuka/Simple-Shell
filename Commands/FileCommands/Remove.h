#ifndef OO1_REMOVE_H
#define OO1_REMOVE_H

#include "FileCmds.h"

class Remove : public FileCmds{
public:
    void execute(Writer* w) override;

};


#endif //OO1_REMOVE_H