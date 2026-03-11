#ifndef OO1_FILEEXCEPTIONS_H
#define OO1_FILEEXCEPTIONS_H
#include <exception>
#include <string>
#include <utility>

class CmdExceptions : public std::exception {
public:
    explicit CmdExceptions(std::string s = "") : txt(std::move(s)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return txt.c_str();
    }

protected:
    std::string txt;
};
//ArgumentErrors
class ArgExp : public CmdExceptions {
public:
    explicit ArgExp() : CmdExceptions("Argument for this command is expected \n") {
    }
};

class ArgNotExp : public CmdExceptions {
public:
    explicit ArgNotExp() : CmdExceptions("Argument for this command is not expected\n") {
    }
};

class ArgInQuotesExp : public CmdExceptions {
public:
    explicit ArgInQuotesExp() : CmdExceptions("Argument in quotes is expected \n") {
    }
};

class TooManyArgs : public CmdExceptions {
public:
    explicit TooManyArgs() : CmdExceptions("Too many arguments \n") {}
};
//FileErrors
class FileFound : public CmdExceptions {
public:
    explicit FileFound(const std::string &s) : CmdExceptions("File already exists " + s) {
    }
};

class FileNotFound : public CmdExceptions {
public:
    explicit FileNotFound(const std::string& s) : CmdExceptions("File is not found " + s) {}
};
//OptionErrors
class NotValidOpt : public CmdExceptions {
public:
    explicit NotValidOpt(const std::string& s) : CmdExceptions("This options is not valid: "+ s +"\n") {}
};

class OptExp : public CmdExceptions {
public:
    explicit OptExp() : CmdExceptions("Option for this command is expected \n") {}
};

class OptInQuotes: public CmdExceptions {
public:
    explicit OptInQuotes() : CmdExceptions("Option in quotes is expected \n") {}
};

class OptIsNegativeNumber: public CmdExceptions {
public:
    explicit OptIsNegativeNumber() : CmdExceptions("Option is negative number \n") {}
};
//RedirectionErrors
class RedirectionNotAllowed : public CmdExceptions {
public:
    explicit RedirectionNotAllowed() : CmdExceptions("Redirection for this command is not allowed \n") {}
};

class InputRedirectionExists : public CmdExceptions {
public:
    explicit InputRedirectionExists() : CmdExceptions("Input redirection already exists\n") {}
};

class OutputRedirectionExists : public CmdExceptions {
public:
    explicit OutputRedirectionExists() : CmdExceptions("Output redirection already exists\n") {}
};

class RedirectioFilenameNotExists : public CmdExceptions {
public:
    explicit RedirectioFilenameNotExists() : CmdExceptions("Redirection filename not exists\n") {}
};
//Cmd and Pipe Errors
class CmdIsEmpty : public CmdExceptions {
public:
    explicit CmdIsEmpty() : CmdExceptions("Command is empty\n") {}
};

class CmdWithoutEntryNotAtBeginning : public CmdExceptions {
public:
    explicit CmdWithoutEntryNotAtBeginning(const std::string& name) : CmdExceptions("A command without an entry is not at the beginning -"+name+"\n") {}
};

class CmdWithoutExitNotAtEnd : public CmdExceptions {
public:
    explicit CmdWithoutExitNotAtEnd(const std::string& name) : CmdExceptions("A command without an entry is not at the end -"+name+"\n") {}
};

class CmdWithArgInPipe: public CmdExceptions {
public:
    explicit CmdWithArgInPipe() : CmdExceptions("A command with argument is in the pipe \n"){}
};

class UnknownCmd : public CmdExceptions {
public:
    explicit UnknownCmd(const std::string& name) : CmdExceptions("Unknown command "+name+"\n") {}
};
//Pipe
class PipeOverLoad : public CmdExceptions {
public:
    explicit PipeOverLoad() : CmdExceptions("Pipe overload\n") {}
};

#endif //OO1_FILEEXCEPTIONS_H
