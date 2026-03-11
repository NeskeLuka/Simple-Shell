#ifndef OO1_EXIT_H
#define OO1_EXIT_H
#include "../Commands/Command.h"

class ExitCommand : public Command {
    public:
     void execute(Writer* w) override;
     void set(std::vector<std::string> v, Reader* r) override;
};

#endif //OO1_EXIT_H
