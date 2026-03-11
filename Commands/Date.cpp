#include "Date.h"
#include <chrono>
#include <iostream>
#include "../CmdExceptions.h"
#include "../Writers/Writer.h"
#include "../Writers/FileWriter.h"
#include <sstream>

void Date::set(const std::vector<std::string> v,  Reader *r) {
    validateArgsNotEmpty(v);
    validateRedirectionIn();
}

void Date::execute(Writer* w) {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm local{};
    localtime_s(&local, &t);

    std::stringstream ss;
    ss << (local.tm_mday < 10 ? "0" : "") << local.tm_mday << ".";
    const int month = local.tm_mon + 1;
    ss << (month < 10 ? "0" : "") << month << ".";
    ss << (local.tm_year + 1900) << ".";

    w->write(ss.str());
}

