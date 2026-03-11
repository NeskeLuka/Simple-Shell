#ifndef OO1_WC_H
#define OO1_WC_H

#include "TxtCommands.h"

class Wc : public TxtCommands {
public:
    void execute(Writer *w) override;

    void set(std::vector<std::string> v, Reader *r) override;

protected:
    std::string arg;

    void validateArg() const;
};

#endif //OO1_WC_H
