#include "Batch.h"
#include <iostream>
#include "../CmdExceptions.h"
using namespace std;

void Batch::execute(Writer *w) {
    validateFileNotFound(filename);

    string line;
    ifstream file(filename);

    while (getline(file, line)) {
        line += "\n";
        try {
            MakeCommand::getInstance()->executeLine(line, w);
        } catch (const CmdExceptions &e) {
            w->write(std::string(e.what()));
        } catch (const exception &e) {
            w->write(std::string(e.what()));
        }
    }
}

void Batch::set(const std::vector<std::string> basic_strings, Reader *r) {
    isBatch = true;
    FileCmds::set(basic_strings, r);
}
