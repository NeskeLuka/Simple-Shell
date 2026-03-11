
#ifndef OO1_BASICCMD_H
#define OO1_BASICCMD_H
#include "../Command.h"


class BasicCmd : public Command {
public:
    void execute(Writer *w) override;

    void set(std::vector<std::string> v, Reader *r) override;
protected:
    std::string opt;
    std::string arg;
};


#endif //OO1_BASICCMD_H