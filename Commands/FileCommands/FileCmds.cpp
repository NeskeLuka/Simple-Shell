#include "../../Commands/FileCommands/FileCmds.h"
#include "../../CmdExceptions.h"
#include "../../Parser/CmdParser.h"
#include "../../Parser/Pipe.h"

void FileCmds::set(const std::vector<std::string> v,  Reader *r) {
    if (const auto ptr = dynamic_cast<Pipe*>(r)) {
        filename = ptr->readLines()[0];
    }else{
        (isBatch)? validateRedirectionIn() : validateRedirectionALL();
        validateArgsEmpty(v);
        filename = v[0];
    }
}

bool FileCmds::fileExists(const std::string &s) {
    const std::ifstream file(s);
    return file.good();
}

bool FileCmds::quoted(const std::string &s) {
    return s.size()>=2 && (s[0] == '"' || s.back() == '"');
}

void FileCmds::validateFileNotFound(const std::string &s) const {
    if (!fileExists(filename)) {
        throw FileNotFound(filename);
    }
}

void FileCmds::validateFileFound(const std::string &s) const {
    if (fileExists(filename)) {
        throw FileFound(filename);
    }
}
