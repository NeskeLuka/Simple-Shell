#ifndef OO1_COMMAND_H
#define OO1_COMMAND_H
#include <vector>
#include <string>

class Reader;
class Writer;
class CmdParser;

class Command {
public:
    virtual ~Command() = default;

    virtual void execute(Writer *w) = 0;

    virtual void set(std::vector<std::string> v, Reader *r) = 0;

    void setParser(CmdParser* p);

    [[nodiscard]] bool CmdWithArg() const;

protected:
    CmdParser* cmdP = nullptr;

    virtual void validateRedirectionIn() const;

    virtual void validateRedirectionOut() const;

    virtual void validateRedirectionALL() const;

    virtual void validateArgsEmpty(const std::vector<std::string>& args) const;

    virtual void validateArgsNotEmpty(const std::vector<std::string>& args) const;

    bool hasArgument = false;
};

inline void Command::setParser(CmdParser *p) {
    this->cmdP = p;
}

inline bool Command::CmdWithArg() const {
    return hasArgument;
}

#endif //OO1_COMMAND_H
