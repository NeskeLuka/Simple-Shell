#ifndef OO1_CMDPARSER_H
#define OO1_CMDPARSER_H
#include <vector>
#include <string>
class Reader;
class Writer;

class CmdParser {
public:
    explicit CmdParser(const std::string &line, Writer *w);

    static std::vector<std::string> parseCommand(const std::string &cmd);

    [[nodiscard]] std::vector<std::string> getCmds() const;

    [[nodiscard]] Reader *getReader() const;

    [[nodiscard]] Writer *getWriter() const;

    [[nodiscard]] bool isInputRedirection() const;

    [[nodiscard]] bool isOutputRedirection() const;

    void setInputRedirection(bool i = false);

    void setOutputRedirection(bool o = false);

protected:
    void parseLine(const std::string &line);

    void readFilename(int &index, const std::string &path);

    void setWriter(const std::string &filename, bool flag);

    void setReader(const std::string &filename);

    static bool isOpen(const std::string &filename);

    Reader *reader;
    Writer *writer;
    std::vector<std::string> cmds;

private:
    bool hasInputRedirection = false;
    bool hasOutputRedirection = false;
    std::vector<int> unexpectedChars = {};

    int pipesNum = 0;

    int inputRedirectionNum = 0;

    int outputRedirectionNum = 0;

    bool validateUnexpectedChars(const std::string &line);

    void validatePipe() const;

    void printError(const std::string &line) const;

    static bool isAllowedOutsideQuotes(char c);

    static bool isAllSpace(const std::string &cmd);
};

inline std::vector<std::string> CmdParser::getCmds() const {
    return cmds;
}

inline Reader *CmdParser::getReader() const {
    return reader;
}

inline Writer *CmdParser::getWriter() const {
    return writer;
}

inline bool CmdParser::isInputRedirection() const {
    return hasInputRedirection;
}

inline bool CmdParser::isOutputRedirection() const {
    return hasOutputRedirection;
}

inline void CmdParser::setInputRedirection(const bool i) {
    hasInputRedirection = i;
}

inline void CmdParser::setOutputRedirection(const bool o) {
    hasOutputRedirection = o;
}
#endif //OO1_CMDPARSER_H
