#ifndef OO1_COMMAND_H
#define OO1_COMMAND_H


class Command {
public:
    Command();

    virtual void execute();

    virtual ~Command() = default;

};


#endif //OO1_COMMAND_H