#ifndef OO1_TIME_H
#define OO1_TIME_H
#include "Command.h"

class TimeCom : public Command {
public:
    void set(std::vector<std::string>, Reader *r) override;

    void execute(Writer *w) override;
};


#endif
