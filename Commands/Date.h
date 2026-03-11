#ifndef OO1_DATE_H
#define OO1_DATE_H

#include "Command.h"

class Date : public Command {
public:
    void set(std::vector<std::string> v, Reader* r) override;

    void execute(Writer* w) override;
};


#endif //OO1_DATE_H