#include "Remove.h"
#include "../../CmdExceptions.h"

void Remove::execute(Writer *w) {
    validateFileNotFound(filename);
    std::remove(filename.c_str());
}
