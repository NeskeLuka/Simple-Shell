#ifndef OO1_ECHO_H
#define OO1_ECHO_H

#include "TxtCommands.h"

class Echo : public TxtCommands {
public:
    void execute(Writer* w) override;
    void set(std::vector<std::string> , Reader* r) override;
protected:
    static void validateTooManyArgs(const std::vector<std::string>& v);
};

#endif //OO1_ECHO_H