#ifndef OO1_MAKECOMMAND_H
#define OO1_MAKECOMMAND_H

#include <memory>
#include <string>
#include <unordered_map>
#include "Writers/Writer.h"
#include "Commands/Command.h"
#include "Commands/Prompt.h"
#include "Commands/Exit.h"

class Reader;
class Command;
class Prompt;

class MakeCommand {
public:
    static MakeCommand *getInstance();

    void run();
protected:
    void display(Writer *w) const;

    bool running;

    Command *getCommand(const std::string &name);

    MakeCommand();

private:
    //singleton design
    static std::unique_ptr<MakeCommand> instance;
    //map of all cmds
    std::unordered_map<std::string, std::unique_ptr<Command> > commands;

    void executeLine(const std::string &line, Writer *w = nullptr);
    //friend class
    friend class Batch;
    //class Exit
    void turnOff();

    friend void ExitCommand::execute(Writer* w);
    //class Prompt;
    void setPrompt(const std::string &s);

    friend void Prompt::execute(Writer *w);

    std::string prompt;
    //validation
    static void validateCmd(const std::string& cmd, int pos, unsigned long long end);
    static void validateCmdWithoutEntry(const std::string& cmd, int pos);
    static void validateCmdWithoutExit(const std::string& cmd, int pos, unsigned long long end);
    static void validateCmdWithArg(const Command* cmd, const std::vector<std::string> & args,int pos);
    static void validateCmdName(const Command* cmd, const std::string& name);
};

inline void MakeCommand::turnOff() {
    running = false;
}

inline void MakeCommand::display(Writer *w) const {
    w->setPrompt(prompt);
    w->write(prompt + " ");
}

inline void MakeCommand::setPrompt(const std::string &s) {
    prompt = s;
}

#endif //OO1_MAKECOMMAND_H
