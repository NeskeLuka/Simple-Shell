#include "Head.h"
#include "../../CmdExceptions.h"

void Head::execute(Writer *w) {
    const int cnt = std::stoi(arg.substr(2));
    for (int i = 0; i < cnt; i++) {
        w->write(txt[i]);
    }
}

void Head::set(std::vector<std::string> v,  Reader *r) {
    validateArgsEmpty(v);
    arg = v[0];
    if (!(arg.find("-n")==0 && arg.size() > 2 && arg.size() < 8) || (std::stoi(arg.substr(2)) < 0))
        throw NotValidOpt(arg);

    std::vector<std::string> inputArgs;
    if (v.size() > 1) {
        inputArgs.insert(inputArgs.end(), v.begin() + 1, v.end());
    }
    loadText(inputArgs, r);
}
