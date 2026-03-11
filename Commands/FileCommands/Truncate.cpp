#include "../../Commands/FileCommands/Truncate.h"

void Truncate::execute(Writer *w) {
    validateFileNotFound(filename);
    std::ofstream f(filename);
}
