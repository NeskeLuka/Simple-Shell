#include "TxtCommands.h"
#include <memory>
#include "../../CmdExceptions.h"
#include "../../Parser/CmdParser.h"
#include "../../Readers/FileReader.h"
#include "../../Readers/Reader.h"
#include "../FileCommands/FileCmds.h"
void TxtCommands::loadText( std::vector<std::string> &source,  Reader *r) {
    txt.clear();
    if (source.empty()) {
        if (r) txt = r->readLines();
        return;
    }
    validateRedirectionIn();
    if (!hasQuotes(source[0]) ) {
        validateFileNotFound(source[0]);
        const auto fr = std::make_unique<FileReader>(source[0]);
        txt = fr->readLines();
        return;
    }
    if (quoted(source[0])) {
        source[0] = source[0].substr(1, source[0].size()-2);
    }else throw ArgInQuotesExp();
    txt = source;
}

bool TxtCommands::quoted(const std::string &s) {
    return s.size()>=2 && (s[0] == '"' && s.back() == '"');
}

bool TxtCommands::hasQuotes(const std::string &s) {
    return s.size()>=2 && (s[0] == '"' || s.back() == '"');
}

bool TxtCommands::inQuotes(const std::string &s) {
    return !s.empty() && s[0]=='\'' && s[s.size()-1]=='\'';
}

std::string TxtCommands::unquote(const std::string &s) {
    return s.substr(1, s.size() - 2);
}

void TxtCommands::validateFileNotFound(const std::string &s) {
    if (!FileCmds::fileExists(s)) {
        throw FileNotFound(s);
    }
}

