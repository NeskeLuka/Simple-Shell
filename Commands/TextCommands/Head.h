#ifndef OO1_HEAD_H
#define OO1_HEAD_H
#include "TxtCommands.h"


class Head  : public TxtCommands{
public:
    void execute(Writer* w) override;
    void set(std::vector<std::string> , Reader* r) override;
protected:
    std::string arg;
};


#endif //OO1_HEAD_H