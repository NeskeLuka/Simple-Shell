#include "TimeCom.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include "../Writers/Writer.h"
#include "../Parser/CmdParser.h"

void TimeCom::set(const std::vector<std::string> v,  Reader *r) {
    validateArgsNotEmpty(v);
    validateRedirectionIn();
}

void TimeCom::execute(Writer *w) {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm local{};
    localtime_s(&local, &t);

    //transformirng time into format
    std::stringstream ss;
    ss << (local.tm_hour < 10 ? "0" : "") << local.tm_hour << ":"
            << (local.tm_min < 10 ? "0" : "") << local.tm_min << ":"
            << (local.tm_sec < 10 ? "0" : "") << local.tm_sec;

    w->write(ss.str());
}
