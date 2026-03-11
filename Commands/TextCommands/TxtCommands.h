#ifndef OO1_TXTCOMMANDS_H
#define OO1_TXTCOMMANDS_H

#include "../Command.h"
#include "../../Writers/Writer.h"

class TxtCommands : public Command {
protected:
    std::vector<std::string> txt;

    void loadText(std::vector<std::string> &source, Reader *r);

    static bool quoted(const std::string &s);

    static bool hasQuotes(const std::string &s);

    static bool inQuotes(const std::string &s);

    static std::string unquote(const std::string &s);

    static void validateFileNotFound(const std::string &s);
};


#endif //OO1_TXTCOMMANDS_H
