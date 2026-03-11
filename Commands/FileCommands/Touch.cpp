#include "../../Commands/FileCommands/Touch.h"
void Touch::execute(Writer *w) {
    validateFileFound(filename);
    std::ofstream f(filename);
}
