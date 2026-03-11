#ifndef OO1_TR_H
#define OO1_TR_H
#include "TxtCommands.h"


class Tr : public TxtCommands {
public:
    void execute(Writer *w) override;

    void set(std::vector<std::string>, Reader *r) override;

protected:
    std::string what;
    std::string with;

    static void validateTr(const std::vector<std::string> &v);

    void validateAll(const std::vector<std::string> &v) const;

    static void validateWith(const std::string& s) ;
};


#endif //OO1_TR_H
