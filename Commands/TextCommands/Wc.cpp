#include "Wc.h"
#include <iostream>
#include <sstream>
#include "../../Readers/FileReader.h"
#include "../../CmdExceptions.h"

void Wc::execute(Writer *w) {
    unsigned int cnt = 0;
    for (const auto &i: txt) {
        if (arg == "-w") {
            std::stringstream ss(i);
            std::string s;
            while (ss >> s)
                cnt++;
        } else if (arg == "-c") {
            cnt += i.size(); //+1 because of \n
        } else {
            throw NotValidOpt(arg);
        }
    }
    w->write(std::to_string(cnt));
}

void Wc::set(const std::vector<std::string> v, Reader *r) {
    validateArgsEmpty(v);
    arg = v[0];
    validateArg();
    std::vector<std::string> inputArgs;
    if (v.size() > 1) {
        inputArgs.insert(inputArgs.end(), v.begin() + 1, v.end());
    }
    loadText(inputArgs, r);
}

void Wc::validateArg() const {
    if (arg.find('-')==std::string::npos || quoted(arg.substr(1,arg.size())))
        throw NotValidOpt(arg);

}
