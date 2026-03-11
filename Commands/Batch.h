#ifndef OO1_BATCH_H
#define OO1_BATCH_H
#include "../MakeCommand.h"
#include "FileCommands/FileCmds.h"


class Batch : public FileCmds {
    public:
    void execute(Writer *w) override;
    void set(std::vector<std::string>, Reader *r) override;
};


#endif //OO1_BATCH_H