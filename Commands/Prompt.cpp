#include "Prompt.h"
#include "../CmdExceptions.h"
#include "../Readers/Reader.h"
#include "../MakeCommand.h"

void Prompt::execute(Writer *w) {
    MakeCommand::getInstance()->setPrompt(s);
}

void Prompt::set(const std::vector<std::string> v,  Reader *r) {
    auto lines = v;
    if (r->isPipe()) {
        lines = r->readLines();
    }
    validateAll(lines);
    s = lines[0].substr(1, lines[0].size()-2);
}

bool Prompt::quoted(const std::string &s) {
    return s.size()>=2 && (s[0] == '"' && s.back() == '"');
}

void Prompt::validateArgInQuotesExp(const std::vector<std::string> &v) {
    if (!quoted(v[0]))
        throw ArgInQuotesExp();
}

void Prompt::validateTooManyArgs(const std::vector<std::string> &v) {
    if (v.size()>1)
        throw TooManyArgs();
}

void Prompt::validateAll(const std::vector<std::string> &v) const {
    validateRedirectionALL();
    validateArgsEmpty(v);
    validateArgInQuotesExp(v);
    validateTooManyArgs(v);
}
