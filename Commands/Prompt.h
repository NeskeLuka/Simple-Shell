#ifndef OO1_PROMT_H
#define OO1_PROMT_H
#include "Command.h"

class Prompt : public Command {
public:
    void execute(Writer *w) override;

    void set(std::vector<std::string> v, Reader *r) override;

protected:
    std::string s;

    bool isPipe=false;

    static bool quoted(const std::string &s);

    static void validateArgInQuotesExp(const std::vector<std::string> &v);

    static void validateTooManyArgs(const std::vector<std::string> &v);

    void validateAll(const std::vector<std::string> &v) const;
};

#endif //OO1_PROMT_H
