#include "Command.h"
#include "../CmdExceptions.h"
#include "../Parser/CmdParser.h"

void Command::validateRedirectionIn() const {
    if (cmdP->isInputRedirection())
        throw RedirectionNotAllowed();
}

void Command::validateRedirectionOut() const {
    if (cmdP->isOutputRedirection())
        throw RedirectionNotAllowed();
}

void Command::validateRedirectionALL() const {
    validateRedirectionIn();
    validateRedirectionOut();
}

void Command::validateArgsEmpty(const std::vector<std::string>& args) const {
    if (args.empty())
        throw  ArgExp();
}

void Command::validateArgsNotEmpty(const std::vector<std::string> &args) const {
    if (!args.empty())
        throw ArgNotExp();
}

