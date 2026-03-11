#include "MakeCommand.h"
using namespace std;

int main() {
    MakeCommand *inst = MakeCommand::getInstance();
    //main function
    inst->run();
    delete inst;
    return 0;
}
