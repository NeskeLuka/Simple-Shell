#include "CmdParser.h"
#include <sstream>
#include <utility>
#include "../Readers/Reader.h"
#include "../Writers/Writer.h"
#include "../Readers/ConsoleReader.h"
#include "../Readers/FileReader.h"
#include "../Writers/FileWriter.h"
#include "../CmdExceptions.h"
using namespace std;

CmdParser::CmdParser(const std::string &line, Writer* w) {
    reader = new ConsoleReader();
    writer = w;
    parseLine(line);
}

vector<string> CmdParser::parseCommand(const string &cmd) {
    vector<string> tokens;
    string token;
    bool quotes = false;

    for (int i = 0; i < cmd.size(); i++) {
        const char c = cmd[i];
        if (c=='\n') continue;

        if (c == '"') quotes = !quotes;

        if (isspace(c) && !quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            continue;
        }
        token += c;

    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

void CmdParser::parseLine(const std::string &line) {
    string cmd;
    bool inQuotes = false;
    unexpectedChars.clear();
    for (int i=0; i < line.size(); i++) {
        const char c = line[i];
        if (c=='"') {
            inQuotes = !inQuotes;
            cmd+=c;
            continue;
        }
        if (!inQuotes) {
            if (!isAllowedOutsideQuotes(c)) {
                unexpectedChars.push_back(i);
                cmd += c;
                continue;
            }
            switch (c) {
                case '|':
                    if (!cmd.empty() && !isAllSpace(cmd)) {
                        cmds.push_back(cmd);
                        cmd.clear();
                    }pipesNum++;
                    break;
                case '>':
                    outputRedirectionNum++;
                case '<':
                    if (c=='<')inputRedirectionNum++;
                    readFilename(i, line);
                    break;
                default:
                    cmd += c;
                    break;
            }
        }else {
            cmd+=c;
        }
    }
    if (!cmd.empty() && !isAllSpace(cmd)) {
        cmds.push_back(cmd);
    }
    if (!validateUnexpectedChars(line))
        return;
    validatePipe();
}

void CmdParser::readFilename(int &index, const std::string &path) {
    const int first_char = index;
    index++; // skip the initial char (< or >)
    bool isUpdate = false;

    if (path[index] == '>' && path[index-1] == '>') {
        isUpdate = true; index++;
    }

    std::string filename;
    while (index < path.size() && path[index]!='|' && path[index]!='>' && path[index]!='<') {
        if (isspace(path[index])) {
            index++;
            continue;
        }
        filename+=path[index++];
    }
    if (filename.empty()) {
        throw RedirectioFilenameNotExists();
    }
    if ((path[index]=='<' && inputRedirectionNum>=1) || (path[index]=='>' && outputRedirectionNum>=2)) {
        unexpectedChars.push_back(index);
        return;
    }
    index--;//because of the while loop we must take one step back
    if (path[first_char] == '<') {
        setReader(filename);
    }else {
        setWriter(filename, isUpdate);
    }
}

void CmdParser::setWriter(const std::string &filename, const bool flag) {
    if (hasOutputRedirection) {
        throw OutputRedirectionExists();
    }
    writer = flag ? new FileWriter(filename, std::ios::app) : new FileWriter(filename);
    hasOutputRedirection = true;
}

void CmdParser::setReader(const std::string &filename) {
    if (!isOpen(filename)) {
        throw FileNotFound(filename);
    }
    if (hasInputRedirection) {
        throw InputRedirectionExists();
    }
    delete reader;
    reader = new FileReader(filename);
    hasInputRedirection = true;
}

bool CmdParser::isOpen(const std::string &filename) {
    std::ifstream file(filename);
    return file.is_open();
}

bool CmdParser::validateUnexpectedChars(const std::string &line) {
    if (!unexpectedChars.empty()) {
        printError(line);
        cmds.clear();
        return false;
    }return true;
}

void CmdParser::validatePipe() const {
    if (pipesNum != 0 && pipesNum + 1> cmds.size()) {
        throw PipeOverLoad();
    }

}

void CmdParser::printError(const std::string &line) const {
    cout<<"Error - unexpected characters:\n";
    cout<<line;
    string output(line.size(),' ');
    for (const int unexpectedChar : unexpectedChars) {
        output[unexpectedChar] = '^';
    }
    cout<<output<<endl;
}

bool CmdParser::isAllowedOutsideQuotes(const char c) {
    if (std::isalnum(static_cast<unsigned char>(c))) {
        return true;
    }
    switch (c) {
        case ' ':  case '\t': case '\n':
        case '|':  case '<':  case '>':
        case '"':
        case '-': case '.': case '_':
            return true;
        default:
            return false;
    }
}

bool CmdParser::isAllSpace(const std::string &cmd) {
    for (const char c : cmd) {
        if (!isspace(c)) {return false;}
    }return true;
}
