#include "Tr.h"

#include <iostream>

#include "../../CmdExceptions.h"
#include "../../Readers/Reader.h"

void Tr::execute(Writer *w) {
    for (std::string line : txt) {
        if (what.empty()) {
            w->write(line);
            continue;
        }
        size_t pos = 0;
        while ((pos = line.find(what, pos)) != std::string::npos) {
            line.replace(pos, what.length(), with);
            pos += with.length();
        }
        w->write(line);
    }
}

void Tr::set(const std::vector<std::string> v,  Reader *r) {
    validateAll(v);
    size_t i = 0;
    if (!v[i].empty() && v[i].find('-') == 0) {
        what = v[i].substr(2, v[i].size() - 3);
        with = (++i < v.size()) ? unquote(v[i]) : std::string{};
        if (i!=v.size())validateWith(v[i]);
        txt = r->readLines();
        return;
    }
    //argument is a filename or a line that needs to be modified
    std::vector arg{v[i++]};
    loadText(arg, r);

    if (i >= v.size() || v[i].find('-') != 0)
        throw ArgExp();
    what = v[i].substr(2, v[i].size() - 3);
    with = (++i < v.size()) ? unquote(v[i]) : std::string{};
    if (i!=v.size())validateWith(v[i]);
}

void Tr::validateTr(const std::vector<std::string>& v) {
    int cnt=0;
    while (cnt < v.size() && v[cnt].find('-')!=0) {
        cnt++;
    }
    if (cnt==v.size()) {
        throw OptExp();
    }
    if (v.size()>3 || cnt>1)
        throw TooManyArgs();
    if (!quoted(v[cnt].substr(1, v[cnt].size() - 1)))
        throw OptInQuotes();

}

void Tr::validateAll(const std::vector<std::string> &v) const {
    validateArgsEmpty(v);
    validateTr(v);
}

void Tr::validateWith(const std::string& s) {
    if (!quoted(s)) {
        throw ArgInQuotesExp();
    }
}
