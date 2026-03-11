#ifndef OO1_TOUCH_H
#define OO1_TOUCH_H

#include "FileCmds.h"

class Touch : public FileCmds {
public:
    void execute(Writer* w) override;
};

#endif //OO1_TOUCH_H