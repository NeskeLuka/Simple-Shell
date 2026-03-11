#include "BasicCmd.h"

void BasicCmd::set(const std::vector<std::string> v, Reader *r) {
    if (v.empty())return;//most likely it won't be the case
    if (v[0].find('-')!=std::string::npos) {
        opt = v[0];
        
    }
}
