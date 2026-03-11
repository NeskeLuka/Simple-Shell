#include "Echo.h"
#include "../../Readers/Reader.h"
#include "../../Writers/Writer.h"
#include "../../CmdExceptions.h"
using namespace std;

void Echo::execute(Writer *w) {
    for (auto & i : txt) {
        w->write(i);
    }
}

void Echo::set( std::vector<std::string> v,  Reader *r) {
    validateTooManyArgs( v);
    loadText(v, r);
}

void Echo::validateTooManyArgs(const std::vector<std::string> &v) {
    if (!v.empty() && v.size()>1) {
        throw TooManyArgs();
    }
}
