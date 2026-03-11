#include "MakeCommand.h"
#include <set>
#include "Parser/CmdParser.h"
#include "ListOfCommands.h"
#include "CmdExceptions.h"
#include "Parser/Pipe.h"
#include "Writers/ConsoleWriter.h"

using namespace std;

std::unique_ptr<MakeCommand> MakeCommand::instance = nullptr;

MakeCommand::MakeCommand() : running(true),
                             prompt("$") {
    //list of all commands that CLI has
    commands["time"] = make_unique<TimeCom>();
    commands["date"] = make_unique<Date>();
    commands["echo"] = make_unique<Echo>();
    commands["wc"] = make_unique<Wc>();
    commands["prompt"] = make_unique<Prompt>();
    commands["touch"] = make_unique<Touch>();
    commands["truncate"] = make_unique<Truncate>();
    commands["rm"] = make_unique<Remove>();
    commands["exit"] = make_unique<ExitCommand>();
    commands["head"] = make_unique<Head>();
    commands["tr"] = make_unique<Tr>();
    commands["batch"] = make_unique<Batch>();
}

MakeCommand *MakeCommand::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<MakeCommand>(new MakeCommand());
    }
    return instance.get();
}

Command *MakeCommand::getCommand(const string &name) {
    if (const auto cmd = commands.find(name); cmd != commands.end()) {
        return cmd->second.get();
    }
    return nullptr;
}

void MakeCommand::run() {
    const auto w = std::make_unique<ConsoleWriter>();
    const auto r = std::make_unique<ConsoleReader>();
    const auto errorW = std::make_unique<ConsoleWriter>();//errorStream
    while (running) {
        display(w.get());
        string line = r->readLine();
        if (r->isEOF()) {
            r->clear();
            continue;
        }
        if (line.empty() || line[0] == '\n')
            continue;

        try {
            executeLine(line, w.get());
        } catch (const CmdExceptions &e) {
            errorW->write(std::string(e.what()));
        } catch (const exception &e) {
            errorW->write(std::string(e.what()));
        }
        w->write("\n");
    }
}

void MakeCommand::executeLine(const std::string &line, Writer *w) {
    auto parser = CmdParser(line, w);
    const auto reader = parser.getReader();
    const auto writer = parser.getWriter();
    const vector<string> cmds = parser.getCmds();
    if (cmds.empty()) return;

    vector<Pipe *> pipes;
    for (int i = 0; i < cmds.size() - 1; i++) {
        pipes.push_back(new Pipe());
    }
    for (int i = 0; i < cmds.size(); i++) {
        vector<string> parts = CmdParser::parseCommand(cmds[i]);
        const string &name = parts.front();
        Command *cmd = getCommand(name);
        validateCmdName(cmd, name);
        cmd->setParser(&parser);
        const vector args(parts.begin() + 1, parts.end());
        validateCmd(name, i, cmds.size());
        Reader *rCur = (i == 0) ? reader : pipes[i - 1];
        Writer *wCur = (i == cmds.size() - 1) ? writer : pipes[i];
        if (i==1)parser.setInputRedirection();
        cmd->set(args, rCur);
        validateCmdWithArg(cmd,args,i);
        cmd->execute(wCur);
    }
    if (writer != w) {
        delete writer;
    }
    delete reader;
    for (const Pipe *p: pipes) delete p;
}

//cmd - is name of the cmd, args are arguments of that command, i - is number to represent order in vectors cmds
void MakeCommand::validateCmd(const std::string &cmd, const int pos, const unsigned long long end) {
    validateCmdWithoutEntry(cmd, pos);
    validateCmdWithoutExit(cmd, pos, end);
}

void MakeCommand::validateCmdWithoutEntry(const std::string &cmd, const int pos) {
    set<std::string> cmdsWithoutEntry = {"time", "date"};
    if (cmdsWithoutEntry.find(cmd) != cmdsWithoutEntry.end() && pos != 0) {
        throw CmdWithoutEntryNotAtBeginning(cmd);
    }
}

void MakeCommand::validateCmdWithoutExit(const std::string &cmd, const int pos, const unsigned long long end) {
    set<std::string> cmdsWithoutExit = {"rm", "truncate", "touch", "prompt", "batch"};
    if (cmdsWithoutExit.find(cmd) != cmdsWithoutExit.end() && pos != end-1) {
        throw CmdWithoutExitNotAtEnd(cmd);
    }
}

void MakeCommand::validateCmdWithArg(const Command* cmd, const std::vector<std::string> &args, const int pos) {
    if (pos !=0  && cmd->CmdWithArg()) {
        throw CmdWithArgInPipe();
    }
}

void MakeCommand::validateCmdName(const Command* cmd, const std::string &name) {
    if (!cmd) {
        throw UnknownCmd(name);
    }
}
