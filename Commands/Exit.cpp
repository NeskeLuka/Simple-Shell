#include "Exit.h"
#include"../MakeCommand.h"

void ExitCommand::execute(Writer *w) {
    MakeCommand::getInstance()->turnOff();
}

void ExitCommand::set(const std::vector<std::string> v, Reader *r) {
    validateRedirectionALL();
    validateArgsNotEmpty(v);
}
